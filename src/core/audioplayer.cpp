#include "audioplayer.h"
#include <QDebug>

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
    , m_buffer(nullptr)
{
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.5);
}

AudioPlayer::~AudioPlayer()
{
    if (m_buffer) {
        m_buffer->close();
        delete m_buffer;
    }
}

bool AudioPlayer::loadAudio(const QByteArray &audioData)
{
    if (audioData.isEmpty()) {
        qWarning() << "Audio data is empty!";
        return false;
    }

    if (m_buffer) {
        m_buffer->close();
        delete m_buffer;
        m_buffer = nullptr;
    }

    m_buffer = new QBuffer(this);
    m_buffer->setData(audioData);
    if (!m_buffer->open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open QBuffer!";
        return false;
    }

    m_player->setSourceDevice(m_buffer, QUrl("audio/mpeg"));
    return true;
}

void AudioPlayer::play()
{
    m_player->play();
}

void AudioPlayer::pause()
{
    m_player->pause();
}

void AudioPlayer::stop()
{
    m_player->stop();
}
