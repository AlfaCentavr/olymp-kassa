#include "OlympKassa.h"
#include "Reader.h"
#include "ui_olympkassa.h"

#include <QFile>
#include <QList>
#include <QTimer>
#include <QDir>
#include <QThread>

OlympKassa::OlympKassa(QFileInfoList *files, QString &pathHttp, QFont &font, int timerInterval, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OlympKassa)
    , pathHttpFile(pathHttp)
    , font(font)
    , files(files)
{
    ui->setupUi(this);
    ui->olympLogo->setFont(font);
    ui->olympLogo->show();
    ui->olympLogo->setText("ОЛИМП КЛИНИК");
 //   image = new QLabel(this);
  //  image->setFrameRect(ui->htmlView->rect());
  //  image->setHidden(true);
  //  playerWidget = new QWidget();
  //  playerWidget->setGeometry(ui->htmlView->rect());
  //  player = new QMediaPlayer(playerWidget);
  //  player->setVideoOutput(playerWidget);
  //  playerWidget->setHidden(true);
    QTimer *timer = new QTimer(this);
    Reader *reader = new Reader(pathHttp);
    QThread *thread = new QThread();
    connect(timer, &QTimer::timeout, reader, &Reader::checkFile);
    connect(thread, &QThread::started, reader, &Reader::checkFile);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(reader, &Reader::updateFile, this, &OlympKassa::simpleSetHtml);
    reader->moveToThread(thread);
    thread->start();
    timer->start(timerInterval * 1000);
}

OlympKassa::~OlympKassa()
{
    delete ui;
}

void OlympKassa::setHtml()
{
    QFile htmlFile(pathHttpFile);
    QByteArray dataHtml;
    QString textHtml;
    if(!htmlFile.open(QIODevice::ReadOnly)) {
        if(!isMediaPlay) {
            isMediaPlay = true;
            playMedia();
        }
        return;
    } else {
        if(ui->htmlView->isHidden()) {
            playerWidget->hide();
            image->hide();
            ui->htmlView->show();
        }
        isMediaPlay = false;
        dataHtml = htmlFile.readAll();
        textHtml = QString(dataHtml);
    }
    textHtml.replace(QRegularExpression("(<BODY STYLE).*(>)"), "<BODY STYLE=\"background-color: #edab71; margin: 0; font-family: Arial; font-size: 8pt; font-style: normal; \">");
    ui->htmlView->setHtml(textHtml);
}

void OlympKassa::simpleSetHtml(QString html) {
    ui->htmlView->setHtml(html);
}

void OlympKassa::playMedia()
{
    foreach(QFileInfo fileInfo, files->toList()) {
        QFile file(fileInfo.absoluteFilePath());
        if(isImage(file)) {
            QPixmap pixmap(fileInfo.absoluteFilePath());
            image->setPixmap(pixmap);
            image->setMask(pixmap.mask());
            if(image->isHidden()) {
                image->show();
                playerWidget->hide();
                ui->htmlView->hide();
            }
        } else if(isVideo(file)) {

        }
    }
    isMediaPlay = false;

}

void OlympKassa::reverseWidget() {
    if(ui->htmlView->isHidden()) {
        ui->htmlView->setHidden(false);
        image->setHidden(true);
    } else {
        ui->htmlView->setHidden(true);
        image->setHidden(false);
    }
}

bool OlympKassa::isImage(QFile &file) {
    return file.fileName().contains(QRegularExpression("(.jpg|.jpeg|.png|.JPG|.JPEG|.PNG)$"));
}

bool OlympKassa::isVideo(QFile &file) {
    return file.fileName().contains(QRegularExpression("(.mp4|.MP4)$"));
}



