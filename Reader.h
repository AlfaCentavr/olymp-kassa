#ifndef READER_H
#define READER_H

#include <QObject>
#include <QTimer>

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader(QString &pathHtml, QObject *parent = nullptr);
    void start();
private:
    QString &pathHtml;
    QByteArray hash;
public slots:
    void checkFile();
signals:
    void updateFile(QString &html);
    void startMedia();
    void stopMedia();
};

#endif // READER_H
