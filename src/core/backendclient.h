#pragma once
#include <QObject>
#include <QWebSocket>

class BackendClient : public QObject
{
    Q_OBJECT

public:
    explicit BackendClient(const QString &host, quint16 port, QObject *parent = nullptr);
    void cancel();
    void config(const QString &element);
    void startRecording();
    void stopRecording();

signals:
    void messageReceived(const QString &message);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onMessageReceived(const QString &message);
    void onBytesWritten(qint64 bytes);

private:
    void sendMessage(const QString &message);

    QWebSocket *socket;
};
