#include "mainwidget.h"
#include <QDebug>
#include <QGraphicsBlurEffect>
#include <QPainter>

MainWidget::MainWidget(QWidget *parent, BackendClient *backendClient)
    : QWidget(parent), ui(new Ui::MainWidget), backendClient(backendClient), recording(false)
{
    ui->setupUi(this);

    audioPlayer = new AudioPlayer();

    setWindowFlags(Qt::FramelessWindowHint);
    ui->output->setVisible(false);
    ui->output->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    ui->output->setTextInteractionFlags(Qt::TextSelectableByMouse);

    connect(ui->recordingButton, &QPushButton::clicked, this, &MainWidget::onRecordButtonClicked);
    connect(backendClient,
            &BackendClient::textMessageReceived,
            this,
            &MainWidget::onTextMessageReceived);
    connect(backendClient,
            &BackendClient::binaryMessageReceived,
            this,
            &MainWidget::onBinaryMessageReceived);
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

void MainWidget::onBinaryMessageReceived(const QByteArray &message)
{
    qDebug() << "Playing message of length" << message.length();
    audioPlayer->appendAudioData(message);
    audioPlayer->play();
}

void MainWidget::onTextMessageReceived(const QString &message)
{
    qDebug() << message;
    if (recording)
        ui->output->setPlainText(message);
    else
        ui->output->setPlainText(ui->output->toPlainText() + message);
    qDebug() << "Recording started: " << message;
}

void MainWidget::onErrorOccurred(const QString &error) {
    ui->output->setPlainText(error);
    qWarning() << "Error: " << error;
}
