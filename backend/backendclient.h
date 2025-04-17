#pragma once
#include <QObject>
#include <QWebSocket>
#include <QtQml>

class BackendClient : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit BackendClient(const QString &host, quint16 port, QObject *parent = nullptr);
    void cancel();
    Q_INVOKABLE void config(const QString &element);
    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();

signals:
    void binaryMessageReceived(const QByteArray &message);
    void textMessageReceived(const QString &message);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onBinaryMessageReceived(const QByteArray &messge);
    void onTextMessageReceived(const QString &message);
    void onBytesWritten(qint64 bytes);

private:
    void sendMessage(const QString &message);

    QWebSocket *socket;
};
