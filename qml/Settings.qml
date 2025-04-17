import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "components"

Rectangle {
    id: settingsScreen
    anchors.fill: parent
    color: "#2c3035"

    signal closed()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Button {
                width: 40
                height: 40
                background: null

                contentItem: Text {
                    text: "\uf060" // FontAwesome back arrow
                    font.family: "FontAwesome"
                    font.pixelSize: 24
                    color: "#e0e5ea"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                onClicked: settingsScreen.closed()
            }

            Text {
                text: "Settings"
                font.pixelSize: 28
                font.weight: Font.Medium
                color: "#ffffff"
                Layout.fillWidth: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#40454a"
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ColumnLayout {
                width: parent.width
                spacing: 24

                SettingsGroup {
                    title: "Audio Recording"
                    configKey: "recording.implementation"
                    options: [
                        { text: "Local", value: "local" },
                        { text: "Remote", value: "remote" }
                    ]
                    defaultValue: "local"
                }

                SettingsGroup {
                    title: "Speech to Text"
                    configKey: "transcription.implementation"
                    options: [
                        { text: "Local", value: "local" },
                        { text: "Cloud", value: "deepgram" }
                    ]
                    defaultValue: "local"
                }

                SettingsGroup {
                    title: "General Answers"
                    configKey: "llm.implementation"
                    options: [
                        { text: "Local", value: "ollama" },
                        { text: "Cloud", value: "deepseek" }
                    ]
                    defaultValue: "ollama"
                }

                SettingsGroup {
                    title: "Parsing"
                    configKey: "parsing.implementation"
                    options: [
                        { text: "Simple", value: "simple" },
                        { text: "Advanced", value: "advanced" }
                    ]
                    defaultValue: "simple"
                }

                SettingsGroup {
                    title: "Output"
                    configKey: "tts.implementation"
                    options: [
                        { text: "Local", value: "local" },
                        { text: "Cloud", value: "elevenlabs" }
                    ]
                    defaultValue: "local"
                }
            }
        }
    }
}
