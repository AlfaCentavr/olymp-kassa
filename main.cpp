#include "Media.h"
#include "OlympKassa.h"

#include <QApplication>
#include <QDir>
#include <QFontDatabase>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings("C:/monitor/settings.ini", QSettings::IniFormat);
    settings.beginGroup("MAIN");
    QString pathHttp = settings.value("PATH_HTML").toString();
    QString fontName = settings.value("FONT_NAME").toString();
    QString mediaPath = settings.value("PATH_MEDIA").toString();
    int lifeIntervalImage = settings.value("IMAGE_INTERVAL").toUInt();
    int fontSize = settings.value("FONT_SIZE").toUInt();
    int timerInterval = settings.value("INTERVAL_READING").toUInt();
    settings.endGroup();
    settings.beginGroup("POSITION");
    int x = settings.value("X").toUInt();
    int y = settings.value("Y").toUInt();
    int dX = settings.value("dX").toUInt();
    int dY = settings.value("dY").toUInt();
    settings.endGroup();
    QFont font(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/res/font/" + fontName)).at(0));
    font.setPointSize(fontSize);
    OlympKassa w(pathHttp, font, timerInterval);
    w.setGeometry(x, y, dX, dY);
    w.setWindowFlag(Qt::FramelessWindowHint);
    w.show();
    Media media(mediaPath, w.getLayout());
    media.changeIntervalImage(lifeIntervalImage);
    QObject::connect(&w, &OlympKassa::playMediaSignal, &media, &Media::playMedia);
    QObject::connect(&w, &OlympKassa::stopMediaSignal, &media, &Media::stopMedia);
    QObject::connect(&media, &Media::signalIsStoped, &w, &OlympKassa::showHtml);
    return a.exec();
}
