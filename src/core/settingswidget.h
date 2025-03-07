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

private slots:
    void onAudioRecording(qint32 id);
    void onTextToSpeech(qint32 id);

private:
    QButtonGroup *audioRecordingGroup;
    QButtonGroup *textToSpeechGroup;
    QSettings *settings;
    Ui::SettingsWidget *ui;
};
