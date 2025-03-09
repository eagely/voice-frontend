#include "mainwindow.h"
#include "backendclient.h"
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    backendClient(new BackendClient("127.0.0.1", 8080, this)),
    stackedWidget(new QStackedWidget(this)),
    mainWidget(new MainWidget(nullptr, backendClient)),
    settingsWidget(new SettingsWidget(nullptr, backendClient))
{
    stackedWidget->addWidget(mainWidget);
    stackedWidget->addWidget(settingsWidget);

    setCentralWidget(stackedWidget);

    connect(mainWidget, &MainWidget::openSettingsWidget, this, &MainWindow::onOpenSettingsWidget);
    connect(settingsWidget, &SettingsWidget::openMainWidget, this, &MainWindow::onOpenMainWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::onOpenMainWidget()
{
    stackedWidget->setCurrentWidget(mainWidget);
}

void MainWindow::onOpenSettingsWidget()
{
    stackedWidget->setCurrentWidget(settingsWidget);
}
