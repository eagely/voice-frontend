#include "settingswidget.h"
#include <QButtonGroup>
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent, BackendClient *backendClient) :
    QWidget(parent),
    backendClient(backendClient),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    settings = new QSettings("eagely", "voice");

    audioRecordingGroup = new QButtonGroup(this);
    speechToTextGroup = new QButtonGroup(this);
    generalAnswersGroup = new QButtonGroup(this);
    parsingGroup = new QButtonGroup(this);
    outputGroup = new QButtonGroup(this);

    audioRecordingGroup->addButton(ui->recorderLocalButton);
    audioRecordingGroup->addButton(ui->recorderRemoteButton);

    speechToTextGroup->addButton(ui->speechToTextLocalButton);
    speechToTextGroup->addButton(ui->speechToTextCloudButton);

    generalAnswersGroup->addButton(ui->generalAnswersLocalButton);
    generalAnswersGroup->addButton(ui->generalAnswersCloudButton);

    parsingGroup->addButton(ui->parsingSimpleButton);
    parsingGroup->addButton(ui->parsingAdvancedButton);

    outputGroup->addButton(ui->outputAudioButton);
    outputGroup->addButton(ui->outputTextButton);

    connect(ui->backButton, &QPushButton::clicked, this, &SettingsWidget::openMainWidget);
    connect(audioRecordingGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &SettingsWidget::onAudioRecordingGroupPressed);
    connect(speechToTextGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &SettingsWidget::onSpeechToTextGroupPressed);
    connect(generalAnswersGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &SettingsWidget::onGeneralAnswersGroupPressed);
    connect(parsingGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &SettingsWidget::onParsingGroupPressed);
    connect(outputGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &SettingsWidget::onOutputGroupPressed);
    const auto groups = findChildren<QButtonGroup *>();
    for (auto group : std::as_const(groups)) {
        connect(group,
                QOverload<int>::of(&QButtonGroup::idClicked),
                this,
                &SettingsWidget::onAnyButtonPressed);
    }
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::onAnyButtonPressed()
{
    modifiedSinceApply = true;
    ui->applyButton->setDisabled(false);
}

void SettingsWidget::onApplyButtonPressed()
{
    modifiedSinceApply = false;
    ui->applyButton->setDisabled(true);
    backendClient->config("A");
}

void SettingsWidget::onAudioRecordingGroupPressed(qint32 id) {
    if (id == audioRecordingGroup->id(ui->recorderLocalButton)) {
        backendClient->config("recording.implementation=local");
    } else if (id == audioRecordingGroup->id(ui->recorderRemoteButton)) {
        backendClient->config("recording.implementation=remote");
    }
}

void SettingsWidget::onSpeechToTextGroupPressed(qint32 id) {
    if (id == speechToTextGroup->id(ui->speechToTextLocalButton)) {
        backendClient->config("transcription.implementation=local");
    } else if (id == speechToTextGroup->id(ui->speechToTextCloudButton)) {
        backendClient->config("transcription.implementation=deepgram");
    }
}

void SettingsWidget::onGeneralAnswersGroupPressed(qint32 id) {
    if (id == generalAnswersGroup->id(ui->generalAnswersLocalButton)) {
        backendClient->config("llm.implementation=ollama");
    } else if (id == generalAnswersGroup->id(ui->generalAnswersCloudButton)) {
        backendClient->config("llm.implementation=deepseek");
    }
}

void SettingsWidget::onParsingGroupPressed(qint32 id) {
    if (id == parsingGroup->id(ui->parsingSimpleButton)) {
        backendClient->config("parsing.implementation=patternmatch");
    } else if (id == parsingGroup->id(ui->parsingAdvancedButton)) {
        backendClient->config("parsing.implementation=rasa");
    }
}

void SettingsWidget::onOutputGroupPressed(qint32 id) {
    if (id == outputGroup->id(ui->outputAudioButton)) {
        backendClient->config("response.response_kind=audio");
    } else if (id == outputGroup->id(ui->outputTextButton)) {
        backendClient->config("response.response_kind=text");
    }
}
