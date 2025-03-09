#include "mainwidget.h"
#include <QDebug>
#include <QGraphicsBlurEffect>
#include <QPainter>

MainWidget::MainWidget(QWidget *parent, BackendClient *backendClient)
    : QWidget(parent), ui(new Ui::MainWidget), backendClient(backendClient), recording(false)
{
    ui->setupUi(this);
    backendClient = new BackendClient("127.0.0.1", 8080, this);

    setWindowFlags(Qt::FramelessWindowHint);
    ui->output->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    ui->output->setTextInteractionFlags(Qt::TextSelectableByMouse);
    connect(ui->recordingButton, &QPushButton::clicked, this, &MainWidget::onRecordButtonClicked);
    connect(backendClient, &BackendClient::recordingStarted, this, &MainWidget::onRecordingStarted);
    connect(backendClient, &BackendClient::errorOccurred, this, &MainWidget::onErrorOccurred);
    connect(ui->menuButton, &QPushButton::clicked, this, &MainWidget::openSettingsWidget);
}

MainWidget::~MainWidget() {
    delete ui;
}

void MainWidget::onRecordButtonClicked() {
    if (recording) {
        backendClient->stopRecording();
    } else {
        backendClient->startRecording();
    }
    recording = !recording;
}

void MainWidget::onRecordingStarted(const QString &message) {
    qDebug() << message;
    if (recording)
        ui->output->setPlainText(message);
    else
        ui->output->setPlainText(ui->output->toPlainText() + message);
    qDebug() << "Recording started: " << message;
}

void MainWidget::onRecordingStopped(const QString &message) {
    ui->output->setPlainText(message);
    qDebug() << "Recording stopped: " << message;
}

void MainWidget::onErrorOccurred(const QString &error) {
    ui->output->setPlainText(error);
    qWarning() << "Error: " << error;
}
