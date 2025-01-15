#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), recording(false)
{
    ui->setupUi(this);
    backendClient = new BackendClient("127.0.0.1", 8080, this);

    connect(ui->recordingButton, &QPushButton::clicked, this, &MainWindow::onRecordButtonClicked);
    connect(backendClient, &BackendClient::recordingStarted, this, &MainWindow::onRecordingStarted);
    connect(backendClient, &BackendClient::recordingStopped, this, &MainWindow::onRecordingStopped);
    connect(backendClient, &BackendClient::errorOccurred, this, &MainWindow::onErrorOccurred);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onRecordButtonClicked() {
    if (recording) {
        backendClient->stopRecording();
    } else {
        backendClient->startRecording();
    }
    recording = !recording;
}

void MainWindow::onRecordingStarted(const QString &message) {
    ui->outputLabel->setText(message);
    qDebug() << "Recording started: " << message;
}

void MainWindow::onRecordingStopped(const QString &message) {
    ui->outputLabel->setText(message);
    qDebug() << "Recording stopped: " << message;
}

void MainWindow::onErrorOccurred(const QString &error) {
    ui->outputLabel->setText(error);
    qWarning() << "Error: " << error;
}
