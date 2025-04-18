#pragma once
#include <QObject>
#include <QWebSocket>
#include <QTimer>

class BackendClient : public QObject
{
    Q_OBJECT

public:
    explicit BackendClient(const QString &host, quint16 port, QObject *parent = nullptr);
    ~BackendClient();

    void cancel();
    Q_INVOKABLE void getConfig();
    Q_INVOKABLE void setConfig(const QString &element);
    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();

signals:
    void textMessageReceived(const QString &message);
    void binaryMessageReceived(const QByteArray &message);
    void configUpdateReceived(const QString &config);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &message);
    void onBytesWritten(qint64 bytes);
    void attemptReconnection();

private:
    void sendMessage(const QString &message);

    QWebSocket *m_socket;
    QString m_host;
    quint16 m_port;
    QTimer *m_reconnectTimer;
    QMap<QString, QString> m_config;
    const int RECONNECT_DELAY_MS = 1000;
};
