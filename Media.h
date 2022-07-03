#ifndef MEDIA_H
#define MEDIA_H

#include <QFile>
#include <QFileInfoList>
#include <QLabel>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QObject>

class Media : public QObject
{
    Q_OBJECT
public:
    Media(QString &mediaPath, QWidget *htmlView, QObject *parent = nullptr);
public slots:
    void playMedia();
    void stopMedia();
private slots:
    void playNext();
    void stopImage();
    void stopVideo();
private:
    QString &mediaPath;
    QFileInfoList *infoList;
    QLabel *imageView;
    QTimer *imageTimer;
    QVideoWidget *videoSink;
    int currentFileIndex;
    QMediaPlayer *player;
    bool isImage(QFile &file);
    bool isVideo(QFile &file);
    void setImageWidget(QFile &file);
    void setVideoWidget(QFile &file);
signals:
    void nextFileSignal();
};

#endif // MEDIA_H
