#pragma once
#include <QObject>
#include <QWebSocket>

class BackendClient : public QObject
{
    Q_OBJECT

public:
    explicit BackendClient(const QString &host, quint16 port, QObject *parent = nullptr);
    void config(const QString &message);
    void startRecording();
    void stopRecording();

signals:
    void recordingStarted(const QString &message);
    void recordingStopped(const QString &message);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onBytesWritten(qint64 bytes);

private:
    void sendMessage(const QString &message);

    QWebSocket *socket;
};
