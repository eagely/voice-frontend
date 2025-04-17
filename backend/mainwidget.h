#pragma once
#include <QGraphicsScene>
#include <QWidget>
#include "audioplayer.h"
#include "backendclient.h"
#include "ui_mainwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr, BackendClient *backendClient = nullptr);
    ~MainWidget();

signals:
    void openSettingsWidget();

private slots:
    void onRecordButtonClicked();
    void onBinaryMessageReceived(const QByteArray &message);
    void onTextMessageReceived(const QString &message);
    void onErrorOccurred(const QString &error);

private:
    Ui::MainWidget *ui;
    AudioPlayer *audioPlayer;
    BackendClient *backendClient;
    bool recording;
};
