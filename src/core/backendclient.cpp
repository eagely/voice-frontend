#include "backendclient.h"
#include <QDebug>
#include <QUrl>
#include <QWebSocket>

BackendClient::BackendClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), socket(new QWebSocket)
{
    connect(socket, &QWebSocket::connected, this, &BackendClient::onConnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &BackendClient::onMessageReceived);
    connect(socket, &QWebSocket::bytesWritten, this, &BackendClient::onBytesWritten);

    QString url = QString("ws://%1:%2").arg(host).arg(port);
    socket->open(QUrl(url));
}

void BackendClient::cancel() {
    sendMessage("AC");
}

void BackendClient::config(const QString &element) {
    sendMessage("C" + element);
}

void BackendClient::startRecording() {
    sendMessage("AI");
}

void BackendClient::stopRecording() {
    sendMessage("AT");
}

void BackendClient::sendMessage(const QString &message) {
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

void BackendClient::onConnected() {
    qDebug() << "Connected to host!";
}

void BackendClient::onMessageReceived(const QString &message) {
    QString text = message;
    qDebug() << "Received message from server:" << message;
    if (text.endsWith("\n ")) {
        text = text.left(text.length() - 2) + " ";
    } else if (text.endsWith("\n")) {
        text.chop(1);
    }
    emit messageReceived(text);
}

void BackendClient::onBytesWritten(qint64 bytes) {
    qDebug() << bytes << "bytes written to WebSocket.";
}
