#pragma once
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include <QMediaPlayer>
#include <QObject>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer();

    bool loadAudio(const QByteArray &audioData);

    void play();
    void pause();
    void stop();

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QBuffer *m_buffer;
};
