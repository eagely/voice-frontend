#include "streamingbuffer.h"
#include <QMutexLocker>
#include "QDebug"
#include <cstring>

StreamingBuffer::StreamingBuffer(QObject *parent)
    : QIODevice(parent)
    , m_readPos(0)
{}

void StreamingBuffer::appendData(const QByteArray &data)
{
    qDebug() << "Appending data of length" << data.length();
    QMutexLocker locker(&m_mutex);
    m_data.append(data);
    emit readyRead();
}

bool StreamingBuffer::open(OpenMode mode)
{
    if (!(mode & QIODevice::ReadOnly))
        return false;
    m_readPos = 0;
    return QIODevice::open(mode);
}

qint64 StreamingBuffer::bytesAvailable() const
{
    QMutexLocker locker(&m_mutex);
    return (m_data.size() - m_readPos) + QIODevice::bytesAvailable();
}

bool StreamingBuffer::isSequential() const
{
    return true;
}

bool StreamingBuffer::atEnd() const
{
    // Even if temporarily no data is available, more data might be appended later.
    // Return false to indicate the stream is not ended.
    return false;
}

qint64 StreamingBuffer::readData(char *data, qint64 maxSize)
{
    QMutexLocker locker(&m_mutex);
    if (m_readPos >= m_data.size())
        return 0;
    qint64 bytesToRead = qMin(maxSize, static_cast<qint64>(m_data.size() - m_readPos));
    memcpy(data, m_data.constData() + m_readPos, bytesToRead);
    m_readPos += bytesToRead;
    return bytesToRead;
}

qint64 StreamingBuffer::writeData(const char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return 0;
}
