#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);

    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onButtonClicked() {
    QString data = ui->plainTextEdit->toPlainText();

    QUrl url("http://localhost:8080/process");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    QNetworkReply *reply = networkManager->post(request, data.toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleNetworkReply(reply);
    });
}

void MainWindow::handleNetworkReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        ui->label->setText(response);
    } else {
        ui->label->setText("Error: " + reply->errorString());
    }

    reply->deleteLater();
}
