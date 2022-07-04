#include "Media.h"

#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QRegularExpression>
#include <QTimer>

Media::Media(QString &mediaPath, QWidget *htmlView, QObject *parent)
    : QObject{parent}
    , mediaPath(mediaPath)
{
    videoSink = new QVideoWidget;
    videoSink->setParent(htmlView->parentWidget());
    videoSink->setGeometry(htmlView->geometry());
    imageView = new QLabel;
    imageView->setParent(htmlView->parentWidget());
    imageView->setGeometry(htmlView->geometry());
    videoSink->hide();
    imageView->hide();
    imageTimer = new QTimer;
    imageTimer->setInterval(intervalUpdateImage);
    player = new QMediaPlayer;
    player->setVideoOutput(videoSink);
    infoList = new QFileInfoList(QDir(mediaPath).entryInfoList(QDir::Files, QDir::Size));
    connect(this, &Media::nextFileSignal, this, &Media::playNext);
    connect(imageTimer, &QTimer::timeout, this, &Media::stopImage);
    connect(player, &QMediaPlayer::videoOutputChanged, this, &Media::stopVideo);
}

bool Media::isImage(QFile &file) {
        return file.fileName().contains(QRegularExpression("(.jpg|.jpeg|.png|.JPG|.JPEG|.PNG)$"));
    }

bool Media::isVideo(QFile &file) {
        return file.fileName().contains(QRegularExpression("(.mp4|.MP4)$"));
}

void Media::playMedia() {
    currentFileIndex = -1; //Стандартный итератор
    if(infoList->empty()) {
        qDebug() << "Список медиа-файлов пуст. Воспроизведение невозможно";
        return;
    }
}

void Media::playNext() {
    currentFileIndex++;
    if(currentFileIndex >= infoList->size()) {
        currentFileIndex = 0;
    }
    QFile file(infoList->at(currentFileIndex).absoluteFilePath());
    if(isImage(file)) {
        setImageWidget(file);
    } else if(isVideo(file)) {
        setVideoWidget(file);
    } else {
        qDebug() << "Неизвестный формат файла";
    }

}

void Media::setVideoWidget(QFile &file) {
    if(videoSink->isHidden()) {
        if(!imageView->isHidden()) {
            imageView->hide();
        }
        videoSink->show();
    }
    player->setSource(QUrl::fromLocalFile(file.fileName()));
    player->play();
}

void Media::setImageWidget(QFile &file) {
    if(imageView->isHidden()) {
        if(!videoSink->isHidden()) {
            videoSink->hide();
        }
        imageView->show();
    }
    imageView->setPixmap(QPixmap(file.fileName()));
    imageView->setMask(imageView->pixmap().mask());
    imageView->update();
    imageTimer->start();
}

void Media::changeIntervalImage(int interval) {
    if(interval > 1000) {
    intervalUpdateImage = interval;
    imageTimer->setInterval(intervalUpdateImage);
    } else {
        qDebug() << "Невозможно установить значение интервала менее 1 секунды";
    }
}

void Media::stopMedia() {
    imageTimer->stop();
    imageView->hide();
    videoSink->hide();
}

void Media::stopImage() {
    imageTimer->stop();
    emit nextFileSignal();
}

void Media::stopVideo() {
    player->stop();
    emit nextFileSignal();
}


