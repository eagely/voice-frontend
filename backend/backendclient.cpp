#include "backendclient.h"
#include <QDebug>
#include <QUrl>
#include <QWebSocket>

BackendClient::BackendClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), m_socket(new QWebSocket), m_host(host), m_port(port),
      m_reconnectTimer(new QTimer(this))
{
    m_reconnectTimer->setInterval(RECONNECT_DELAY_MS);
    m_reconnectTimer->setSingleShot(false);

    connect(m_socket, &QWebSocket::connected, this, &BackendClient::onConnected);
    connect(m_socket, &QWebSocket::disconnected, this, &BackendClient::onDisconnected);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &BackendClient::onError);
    connect(m_socket, &QWebSocket::textMessageReceived,
            this, &BackendClient::onTextMessageReceived);
    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &BackendClient::onBinaryMessageReceived);
    connect(m_socket, &QWebSocket::bytesWritten, this, &BackendClient::onBytesWritten);
    connect(m_reconnectTimer, &QTimer::timeout, this, &BackendClient::attemptReconnection);

    attemptReconnection();
}

BackendClient::~BackendClient()
{
    m_reconnectTimer->stop();
    m_socket->deleteLater();
}

void BackendClient::cancel() {
    sendMessage("AC");
}

void BackendClient::getConfig() {
    qDebug() << "Requesting current configuration state from server.";
    sendMessage("G");
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
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QString fullMessage = message;
        if (!message.endsWith('\n')) {
            fullMessage += '\n';
        }
        m_socket->sendTextMessage(fullMessage);
        qDebug() << "Message sent:" << message;
    } else {
        qDebug() << "WebSocket not connected.";
        emit errorOccurred("Socket not connected.");
    }
}

void BackendClient::onConnected()
{
    qDebug() << "Connected to host!";
    m_reconnectTimer->stop();
    getConfig();
}

void BackendClient::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    if (!m_reconnectTimer->isActive()) {
        m_reconnectTimer->start();
    }
}

void BackendClient::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    if (m_socket->state() != QAbstractSocket::ConnectedState && !m_reconnectTimer->isActive()) {
        m_reconnectTimer->start();
    }
}

void BackendClient::attemptReconnection()
{
    if (m_socket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "Attempting to reconnect...";
        QString url = QString("ws://%1:%2").arg(m_host).arg(m_port);
        m_socket->open(QUrl(url));
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

    if (text.startsWith("O")) {
        qDebug() << "Received text:" << text.mid(1);
        emit textMessageReceived(text.mid(1));
    }
    else if (text.startsWith("C")) {
        qDebug() << "Received configuration update:" << text.mid(1);
        emit configUpdateReceived(text.mid(1));
    }
}

void BackendClient::onBinaryMessageReceived(const QByteArray &message)
{
    emit binaryMessageReceived(message);
}

void BackendClient::onBytesWritten(qint64 bytes)
{
    qDebug() << bytes << "bytes written to WebSocket.";
}
