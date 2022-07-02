#ifndef OLYMPKASSA_H
#define OLYMPKASSA_H

#include <QFile>
#include <QFileInfoList>
#include <QLabel>
#include <QMainWindow>
#include <QRegularExpression>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class OlympKassa; }
QT_END_NAMESPACE

class OlympKassa : public QMainWindow
{
    Q_OBJECT

public:
   // OlympKassa(QFileInfoList *files, QWidget *parent = nullptr);
    OlympKassa(QFileInfoList *files, QString &pathHttp, QFont &font, int timerInterval, QWidget *parent = nullptr);
    ~OlympKassa();
public slots:
    void simpleSetHtml(QString html);
private:
    Ui::OlympKassa *ui;
    bool isMediaPlay = false;
    QString &pathHttpFile;
    QFont &font;
    QLabel *image;
    QMediaPlayer *player;
    QWidget *playerWidget;
    QFileInfoList *files;
    bool isImage(QFile &file);
    bool isVideo(QFile &file);
private slots:
    void setHtml();
    void playMedia();
    void reverseWidget();
};
#endif // OLYMPKASSA_H
