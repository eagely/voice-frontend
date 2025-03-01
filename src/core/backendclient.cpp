#include "backendclient.h"
#include <QDebug>
#include <QUrl>
#include <QWebSocket>

BackendClient::BackendClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), socket(new QWebSocket)
{
    connect(socket, &QWebSocket::connected, this, &BackendClient::onConnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &BackendClient::onTextMessageReceived);
    connect(socket, &QWebSocket::bytesWritten, this, &BackendClient::onBytesWritten);

    QString url = QString("ws://%1:%2").arg(host).arg(port);
    socket->open(QUrl(url));
}

void BackendClient::startRecording() {
    sendMessage("START_RECORDING");
}

void BackendClient::stopRecording() {
    sendMessage("STOP_RECORDING");
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

void BackendClient::onTextMessageReceived(const QString &message) {
    QString text = message;
    if (text.endsWith("\n ")) {
        text = text.left(text.length() - 2) + " ";
    } else if (text.endsWith("\n")) {
        text.chop(1);
    }
    emit recordingStarted(text);
}

void BackendClient::onBytesWritten(qint64 bytes) {
    qDebug() << bytes << "bytes written to WebSocket.";
}
