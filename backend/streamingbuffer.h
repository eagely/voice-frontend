#pragma once
#include <QByteArray>
#include <QIODevice>
#include <QMutex>

class StreamingBuffer : public QIODevice
{
    Q_OBJECT
public:
    explicit StreamingBuffer(QObject *parent = nullptr);

    void appendData(const QByteArray &data);

    bool open(OpenMode mode) override;
    qint64 bytesAvailable() const override;
    bool isSequential() const override;
    bool atEnd() const override;

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    mutable QMutex m_mutex;
    QByteArray m_data;
    qint64 m_readPos;
};
