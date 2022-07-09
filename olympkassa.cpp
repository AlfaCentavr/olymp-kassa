#include "OlympKassa.h"
#include "Reader.h"
#include "ui_olympkassa.h"

#include <QFile>
#include <QList>
#include <QTimer>
#include <QDir>
#include <QThread>

OlympKassa::OlympKassa(QString &pathHttp, QFont &font, int timerInterval, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OlympKassa)
    , pathHttpFile(pathHttp)
    , font(font)
{
    ui->setupUi(this);
    ui->olympLogo->setFont(font);
    ui->olympLogo->show();
    ui->olympLogo->setText("ОЛИМП КЛИНИК");
    QTimer *timer = new QTimer(this);
    Reader *reader = new Reader(pathHttp);
    QThread *thread = new QThread();
    connect(timer, &QTimer::timeout, reader, &Reader::checkFile);
    connect(thread, &QThread::started, reader, &Reader::checkFile);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(reader, &Reader::updateFile, this, &OlympKassa::simpleSetHtml);
    connect(reader, &Reader::startMedia, this, &OlympKassa::hideHtml);
    connect(reader, &Reader::stopMedia, this, &OlympKassa::stopMediaSignal);
    reader->moveToThread(thread);
    thread->start();
    timer->start(timerInterval * 1000);
}

OlympKassa::~OlympKassa()
{
    delete ui;
}


void OlympKassa::simpleSetHtml(QString html) {
    if(ui->htmlView->isHidden()) {
        ui->htmlView->show();
    }
    ui->htmlView->setHtml(html);
}

void OlympKassa::hideHtml() {
    ui->olympLogo->hide();
    ui->widget->hide();
    ui->centralwidget->setStyleSheet(mediaStyle);
    qDebug() << "OlympKassa::hideHtml() ~~~~~ OlympKassa emit playMediaSignal";
    emit playMediaSignal();
}

void OlympKassa::showHtml() {
    ui->centralwidget->setStyleSheet(htmlStyle);
    ui->widget->show();
    ui->olympLogo->show();
}

QLayout *OlympKassa::getLayout() {
    return  ui->verticalLayout_2;
}



