#include "backendclient.h"
#include <QDebug>

BackendClient::BackendClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &BackendClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &BackendClient::onReadyRead);
    connect(socket, &QTcpSocket::bytesWritten, this, &BackendClient::onBytesWritten);

    socket->connectToHost(host, port);
}

void BackendClient::startRecording() {
    sendMessage("START_RECORDING");
}

void BackendClient::stopRecording() {
    sendMessage("STOP_RECORDING");
}

void BackendClient::sendMessage(const QString &message) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        QString fullMessage = message;
        if (!message.endsWith('\n')) {
            fullMessage += '\n';
        }

        socket->write(fullMessage.toUtf8());
        qDebug() << "Message sent: " << message;
    } else {
        qDebug() << "Socket not connected.";
        emit errorOccurred("Socket not connected.");
    }
}

void BackendClient::onConnected() {
    qDebug() << "Connected to host!";
}

void BackendClient::onReadyRead() {
    QByteArray data = socket->readAll();
    emit recordingStarted(QString::fromUtf8(data));
}

void BackendClient::onBytesWritten(qint64 bytes) {
    qDebug() << bytes << "bytes written to socket.";
}
