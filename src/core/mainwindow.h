#pragma once
#include "backendclient.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRecordButtonClicked();
    void onRecordingStarted(const QString &message);
    void onRecordingStopped(const QString &message);
    void onErrorOccurred(const QString &error);

private:
    Ui::MainWindow *ui;
    BackendClient *backendClient;
    bool recording;
};
