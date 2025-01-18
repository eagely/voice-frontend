#include "settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    settings = new QSettings("eagely", "voice");

    connect(ui->backButton, &QPushButton::clicked, this, &SettingsWidget::openMainWidget);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}
