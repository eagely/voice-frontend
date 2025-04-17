#include "audioplayer.h"
#include <QDebug>
#include "streamingbuffer.h"

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
    , m_streamBuffer(new StreamingBuffer(this))
{
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.5);

    m_streamBuffer->open(QIODevice::ReadOnly);
    m_player->setSourceDevice(m_streamBuffer, QUrl("audio/mpeg"));
}

bool AudioPlayer::appendAudioData(const QByteArray &audioData)
{
    if (audioData.isEmpty()) {
        qWarning() << "Received empty audio data!";
        return false;
    }
    m_streamBuffer->appendData(audioData);
    play();
    return true;
}

void AudioPlayer::play()
{
    m_player->play();
}
