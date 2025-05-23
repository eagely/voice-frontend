#pragma once
#include "backendclient.h"
#include "mainwidget.h"
#include "settingswidget.h"
#include <QMainWindow>
#include <QWidget>
#include <qstackedwidget.h>
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
    void onOpenMainWidget();
    void onOpenSettingsWidget();

private:
    BackendClient *backendClient;
    QStackedWidget *stackedWidget;
    MainWidget *mainWidget;
    SettingsWidget *settingsWidget;
};
