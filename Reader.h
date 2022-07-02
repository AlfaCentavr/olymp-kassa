#ifndef READER_H
#define READER_H

#include <QObject>
#include <QTimer>

class Reader : public QObject
{
    Q_OBJECT
public:
  //  explicit Reader(QObject *parent = nullptr);
    Reader(QString &pathHtml, QObject *parent = nullptr);
    void start();
private:
    QString &pathHtml;
    QByteArray hash;
public slots:
    void checkFile();
signals:
    void updateFile(QString &html);
};

#endif // READER_H
