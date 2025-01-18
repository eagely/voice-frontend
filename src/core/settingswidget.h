#pragma once
#include <QSettings>
#include <QWidget>
#include "ui_settingswidget.h"

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

signals:
    void openMainWidget();

private:
    Ui::SettingsWidget *ui;
    QSettings *settings;
};
