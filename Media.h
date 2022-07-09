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
    Media(QString &mediaPath, QLayout *layout, QObject *parent = nullptr);
    void changeIntervalImage(int interval);
public slots:
    void playMedia();
    void stopMedia();
private slots:
    void playNext();
    void stopImage();
    void stopVideo(QMediaPlayer::PlaybackState rate);
private:
    QString &mediaPath;
    QFileInfoList *infoList;
    QLabel *imageView;
    QTimer *imageTimer;
    QVideoWidget *videoSink;
    QMediaPlayer *player;
    bool isPlay = false;
    int currentFileIndex;
    int intervalUpdateImage = 4000;
    bool isImage(QFile &file);
    bool isVideo(QFile &file);
    void setImageWidget(QFile &file);
    void setVideoWidget(QFile &file);
signals:
    void nextFileSignal();
    void signalIsStoped();
};

#endif // MEDIA_H
