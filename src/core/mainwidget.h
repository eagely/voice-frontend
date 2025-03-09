#pragma once
#include "backendclient.h"
#include "ui_mainwidget.h"
#include <QGraphicsScene>
#include <QWidget>

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
    void onRecordingStarted(const QString &message);
    void onRecordingStopped(const QString &message);
    void onErrorOccurred(const QString &error);

private:
    Ui::MainWidget *ui;
    BackendClient *backendClient;
    bool recording;
};
