#pragma once
#include <QSettings>
#include <QWidget>
#include "backendclient.h"
#include "ui_settingswidget.h"

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr, BackendClient *backendClient = nullptr);
    ~SettingsWidget();

signals:
    void openMainWidget();

private slots:
    void onAudioRecordingGroupPressed(qint32 id);
    void onSpeechToTextGroupPressed(qint32 id);
    void onGeneralAnswersGroupPressed(qint32 id);
    void onParsingGroupPressed(qint32 id);
    void onOutputGroupPressed(qint32 id);

private:
    QButtonGroup *audioRecordingGroup;
    QButtonGroup *speechToTextGroup;
    QButtonGroup *generalAnswersGroup;
    QButtonGroup *parsingGroup;
    QButtonGroup *outputGroup;

    BackendClient *backendClient;
    QSettings *settings;
    Ui::SettingsWidget *ui;
};
