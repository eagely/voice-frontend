#include "settingswidget.h"
#include <QButtonGroup>
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
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
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::onAudioRecordingGroupPressed(qint32 id) {
    if (id == audioRecordingGroup->id(ui->recorderLocalButton)) {
        qDebug() << "Audio Recording selected: Local";
    } else if (id == audioRecordingGroup->id(ui->recorderRemoteButton)) {
        qDebug() << "Audio Recording selected: Remote";
    }
}

void SettingsWidget::onSpeechToTextGroupPressed(qint32 id) {
    if (id == speechToTextGroup->id(ui->speechToTextLocalButton)) {
        qDebug() << "Speech-To-Text selected: Local";
    } else if (id == speechToTextGroup->id(ui->speechToTextCloudButton)) {
        qDebug() << "Speech-To-Text selected: Cloud";
    }
}

void SettingsWidget::onGeneralAnswersGroupPressed(qint32 id) {
    if (id == generalAnswersGroup->id(ui->generalAnswersLocalButton)) {
        qDebug() << "General Answers selected: Local";
    } else if (id == generalAnswersGroup->id(ui->generalAnswersCloudButton)) {
        qDebug() << "General Answers selected: Cloud";
    }
}

void SettingsWidget::onParsingGroupPressed(qint32 id) {
    if (id == parsingGroup->id(ui->parsingSimpleButton)) {
        qDebug() << "Parsing selected: Simple";
    } else if (id == parsingGroup->id(ui->parsingAdvancedButton)) {
        qDebug() << "Parsing selected: Advanced";
    }
}

void SettingsWidget::onOutputGroupPressed(qint32 id) {
    if (id == outputGroup->id(ui->outputAudioButton)) {
        qDebug() << "Output selected: Audio";
    } else if (id == outputGroup->id(ui->outputTextButton)) {
        qDebug() << "Output selected: Text";
    }
}
