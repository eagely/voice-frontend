#pragma once
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include "streamingbuffer.h"

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);

    bool appendAudioData(const QByteArray &audioData);

    void play();
    void pause();
    void stop();

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    StreamingBuffer *m_streamBuffer;
};
