#include "settingswidget.h"
#include <QButtonGroup>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    settings = new QSettings("eagely", "voice");

    audioRecordingGroup = new QButtonGroup();
    textToSpeechGroup = new QButtonGroup();

    audioRecordingGroup->addButton(ui->recorderLocalButton);
    audioRecordingGroup->addButton(ui->recorderRemoteButton);

    textToSpeechGroup->addButton(ui->transcriberLocalWhisperButton);
    textToSpeechGroup->addButton(ui->trancriberOpenAIApiWhisperButton);
    textToSpeechGroup->addButton(ui->transcriberRemoteWhisperButton);

    connect(ui->backButton, &QPushButton::clicked, this, &SettingsWidget::openMainWidget);
    connect(audioRecordingGroup, &QButtonGroup::idClicked, this, &SettingsWidget::onAudioRecording);
    connect(textToSpeechGroup, &QButtonGroup::idClicked, this, &SettingsWidget::onTextToSpeech);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::onAudioRecording(qint32 id) {
    if (id == audioRecordingGroup->id(ui->recorderLocalButton)) {
        qDebug() << "Audio Recording selected: Local Recorder";
    } else if (id == audioRecordingGroup->id(ui->recorderRemoteButton)) {
        qDebug() << "Audio Recording selected: Remote Recorder";
    }
}

void SettingsWidget::onTextToSpeech(qint32 id) {
    if (id == textToSpeechGroup->id(ui->transcriberLocalWhisperButton)) {
        qDebug() << "Text-To-Speech selected: Local Whisper";
    } else if (id == textToSpeechGroup->id(ui->trancriberOpenAIApiWhisperButton)) {
        qDebug() << "Text-To-Speech selected: OpenAI API Whisper";
    } else if (id == textToSpeechGroup->id(ui->transcriberRemoteWhisperButton)) {
        qDebug() << "Text-To-Speech selected: Remote Whisper";
    }
}
