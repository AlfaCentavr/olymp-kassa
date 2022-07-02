#include "OlympKassa.h"

#include <QApplication>
#include <QDir>
#include <QFontDatabase>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFileInfoList *infoList = new QFileInfoList(QDir("D:/monitor/media").entryInfoList(QDir::Files, QDir::Size));
    QSettings settings("C:/monitor/settings.ini", QSettings::IniFormat);
    settings.beginGroup("MAIN");
    QString pathHttp = settings.value("PATH_HTML").toString();
    QString fontName = settings.value("FONT_NAME").toString();
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
    OlympKassa w(infoList, pathHttp, font, timerInterval);
    w.setGeometry(x, y, dX, dY);
    w.setWindowFlag(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
