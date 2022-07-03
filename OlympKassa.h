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
    OlympKassa(QString &pathHttp, QFont &font, int timerInterval, QWidget *parent = nullptr);
    ~OlympKassa();
    QWidget* getHtmlView();
public slots:
    void simpleSetHtml(QString html);
    void hideHtml();
    void showHtml();
private:
    Ui::OlympKassa *ui;
    bool isMediaPlay = false;
    QString &pathHttpFile;
    QFont &font;
signals:
    void playMediaSignal();
    void stopMediaSignal();
};
#endif // OLYMPKASSA_H
