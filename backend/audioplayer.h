#pragma once
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QtQml>
#include "streamingbuffer.h"

class AudioPlayer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AudioPlayer(QObject *parent = nullptr);
    Q_INVOKABLE bool appendAudioData(const QByteArray &audioData);
    Q_INVOKABLE void play();

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    StreamingBuffer *m_streamBuffer;
};
