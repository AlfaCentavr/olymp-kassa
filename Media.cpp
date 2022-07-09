#include "Media.h"

#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QRegularExpression>
#include <QTimer>
#include <QLayout>

Media::Media(QString &mediaPath, QLayout *layout, QObject *parent)
    : QObject{parent}
    , mediaPath(mediaPath)
{
    videoSink = new QVideoWidget;
    videoSink->hide();
    videoSink->setParent(layout->parentWidget());
    videoSink->setMinimumSize(layout->minimumSize());
    layout->addWidget(videoSink);
    imageView = new QLabel;
    imageView->setAlignment(Qt::AlignCenter);
    imageView->hide();
    imageView->setParent(layout->parentWidget());
    imageView->setMinimumSize(layout->minimumSize());
    layout->addWidget(imageView);
    imageTimer = new QTimer;
    imageTimer->setInterval(intervalUpdateImage);
    player = new QMediaPlayer;
    player->setVideoOutput(videoSink);
    infoList = new QFileInfoList(QDir(mediaPath).entryInfoList(QDir::Files, QDir::Size));
    connect(this, &Media::nextFileSignal, this, &Media::playNext);
    connect(imageTimer, &QTimer::timeout, this, &Media::stopImage);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &Media::stopVideo);
}

bool Media::isImage(QFile &file) {
        return file.fileName().contains(QRegularExpression("(.jpg|.jpeg|.png|.JPG|.JPEG|.PNG)$"));
    }

bool Media::isVideo(QFile &file) {
        return file.fileName().contains(QRegularExpression("(.mp4|.MP4)$"));
}

void Media::playMedia() {
    if(isPlay) {
        return;
    }
    isPlay = true;
    currentFileIndex = -1; //Стандартный итератор
    if(infoList->empty()) {
        qDebug() << "Media set is empty";
        return;
    }
    emit nextFileSignal();
}

void Media::playNext() {
    if(!isPlay) {
        return;
    }
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
        qDebug() << "Unknown file format: " + file.fileName();
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
    if(imageView->isHidden() && isPlay) {
        if(!videoSink->isHidden()) {
            videoSink->hide();
        }
        imageView->show();
    }
    imageView->setPixmap(QPixmap(file.fileName()).scaled(imageView->size(), Qt::KeepAspectRatio));
    imageView->setMask(imageView->pixmap().mask());
    imageView->update();
    imageTimer->start();
}

void Media::changeIntervalImage(int interval) {
    interval *= 1000;
    if(interval >= 1000) {
    intervalUpdateImage = interval;
    imageTimer->setInterval(intervalUpdateImage);
    } else {
        qDebug() << "Doesn't set interval time value less than one second";
    }
}

void Media::stopMedia() {
    isPlay = false;
    imageTimer->stop();
    imageView->hide();
    videoSink->hide();
    player->stop();
E    emit signalIsStoped();
}

void Media::stopImage() {
    imageTimer->stop();
    emit nextFileSignal();
}

void Media::stopVideo(QMediaPlayer::PlaybackState rate) {
    if(rate == QMediaPlayer::PausedState || rate == QMediaPlayer::StoppedState) {
        player->stop();
        emit nextFileSignal();
    }
}


