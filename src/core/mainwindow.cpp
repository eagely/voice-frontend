#include "mainwindow.h"
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    stackedWidget(new QStackedWidget(this)),
    mainWidget(new MainWidget),
    settingsWidget(new SettingsWidget)
{
    setWindowTitle("Widget Switcher");

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
