#include "backendclient.h"
#include <QDebug>
#include <QUrl>
#include <QWebSocket>

BackendClient::BackendClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), socket(new QWebSocket), m_host(host), m_port(port),
      reconnectTimer(new QTimer(this))
{
    reconnectTimer->setInterval(RECONNECT_DELAY_MS);
    reconnectTimer->setSingleShot(false);

    connect(socket, &QWebSocket::connected, this, &BackendClient::onConnected);
    connect(socket, &QWebSocket::disconnected, this, &BackendClient::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &BackendClient::onError);
    connect(socket, &QWebSocket::textMessageReceived,
            this, &BackendClient::onTextMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &BackendClient::onBinaryMessageReceived);
    connect(socket, &QWebSocket::bytesWritten, this, &BackendClient::onBytesWritten);
    connect(reconnectTimer, &QTimer::timeout, this, &BackendClient::attemptReconnection);

    attemptReconnection();
}

BackendClient::~BackendClient()
{
    reconnectTimer->stop();
    socket->deleteLater();
}

void BackendClient::cancel() {
    sendMessage("AC");
}

void BackendClient::setConfig(const QString &element) {
    sendMessage("C" + element);
}

void BackendClient::startRecording() {
    sendMessage("AI");
}

void BackendClient::stopRecording() {
    sendMessage("AT");
}

void BackendClient::sendMessage(const QString &message)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QString fullMessage = message;
        if (!message.endsWith('\n')) {
            fullMessage += '\n';
        }
        socket->sendTextMessage(fullMessage);
        qDebug() << "Message sent:" << message;
    } else {
        qDebug() << "WebSocket not connected.";
        emit errorOccurred("Socket not connected.");
    }
}

void BackendClient::onConnected()
{
    qDebug() << "Connected to host!";
    reconnectTimer->stop();
}

void BackendClient::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    if (!reconnectTimer->isActive()) {
        reconnectTimer->start();
    }
}

void BackendClient::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    if (socket->state() != QAbstractSocket::ConnectedState && !reconnectTimer->isActive()) {
        reconnectTimer->start();
    }
}

void BackendClient::attemptReconnection()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "Attempting to reconnect...";
        QString url = QString("ws://%1:%2").arg(m_host).arg(m_port);
        socket->open(QUrl(url));
    }
}

void BackendClient::onTextMessageReceived(const QString &message)
{
    QString text = message;
    if (text.endsWith("\n ")) {
        text = text.left(text.length() - 2) + " ";
    } else if (text.endsWith("\n")) {
        text.chop(1);
    }
    emit textMessageReceived(text);
}

void BackendClient::onBinaryMessageReceived(const QByteArray &message)
{
    emit binaryMessageReceived(message);
}

void BackendClient::onBytesWritten(qint64 bytes)
{
    qDebug() << bytes << "bytes written to WebSocket.";
}
