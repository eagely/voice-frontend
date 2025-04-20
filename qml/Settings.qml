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
                    text: "\uf060"
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

                RowLayout {
                    SettingsRadioButtonGroup {
                        id: recordingImplementation
                        title: "Audio Recording"
                        configKey: "recording.implementation"
                        options: [
                            { text: "Local", value: "local" },
                            { text: "Remote", value: "remote" }
                        ]
                        defaultValue: "local"
                    }

                    SettingsTextInput {
                        visible: recordingImplementation.selectedValue === "local"
                        title: "Device Name"
                        configKey: "recording.device_name"
                        defaultValue: "pipewire"
                    }

                    SettingsTextInput {
                        visible: recordingImplementation.selectedValue === "local"
                        title: "Wake Word File"
                        configKey: "recording.wake_word"
                        defaultValue: "ferris.ppn"
                    }

                    SettingsTextInput {
                        visible: recordingImplementation.selectedValue === "remote"
                        title: "Remote URL"
                        configKey: "recording.remote_url"
                        defaultValue: "ws://localhost:5555/"
                    }
                }


                RowLayout {
                    SettingsRadioButtonGroup {
                        id: transcriptionImplementation
                        title: "Speech to Text"
                        configKey: "transcription.implementation"
                        options: [
                        { text: "Local Whisper", value: "local" },
                        { text: "Deepgram", value: "deepgram" }
                        ]
                        defaultValue: "local"
                    }

                    SettingsTextInput {
                        visible: transcriptionImplementation.selectedValue === "local"
                        title: "Model File"
                        configKey: "transcription.local_model_path"
                        defaultValue: "base.bin"
                    }

                    SettingsTextInput {
                        visible: transcriptionImplementation.selectedValue === "local"
                        title: "Use GPU"
                        configKey: "transcription.local_use_gpu"
                        defaultValue: "true"
                    }

                    SettingsTextInput {
                        visible: transcriptionImplementation.selectedValue === "deepgram"
                        title: "Deepgram Base URL"
                        configKey: "transcription.deepgram_base_url"
                        defaultValue: "https://api.deepgram.com/v1/"
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 24
                
                    SettingsRadioButtonGroup {
                        id: llmImplementation
                        title: "General Answers"
                        configKey: "llm.implementation"
                        options: [
                            { text: "Ollama", value: "ollama" },
                            { text: "DeepSeek API", value: "deepseek" }
                        ]
                        defaultValue: "ollama"
                    }
                
                    SettingsTextInput {
                        visible: llmImplementation.selectedValue === "deepseek"
                        title: "DeepSeek Base URL"
                        configKey: "llm.deepseek_base_url"
                        defaultValue: "https://api.deepseek.com/"
                    }

                    SettingsTextInput {
                        visible: llmImplementation.selectedValue === "deepseek"
                        title: "DeepSeek Model"
                        configKey: "llm.deepseek_model"
                        defaultValue: "deepseek-chat"
                    }

                    SettingsTextInput {
                        visible: llmImplementation.selectedValue === "ollama"
                        title: "Ollama Base URL"
                        configKey: "llm.ollama_base_url"
                        defaultValue: "http://localhost:11434/"
                    }

                    SettingsTextInput {
                        visible: llmImplementation.selectedValue === "ollama"
                        title: "Ollama Model"
                        configKey: "llm.ollama_model"
                        defaultValue: "deepseek-r1:7b"
                    }
                }

                RowLayout {
                    SettingsRadioButtonGroup {
                        id: parsingImplementation
                        title: "Parsing"
                        configKey: "parsing.implementation"
                        options: [
                            { text: "Pattern Matching", value: "patternmatch" },
                            { text: "Rasa", value: "rasa" }
                        ]
                        defaultValue: "patternmatch"
                    }

                    SettingsTextInput {
                        visible: parsingImplementation.selectedValue === "rasa"
                        title: "Rasa Base URL"
                        configKey: "parsing.rasa_base_url"
                        defaultValue: "http://localhost:5005/"
                    }
                }

                RowLayout {
                    SettingsRadioButtonGroup {
                        id: synthesisImplementation
                        title: "Text-to-speech"
                        configKey: "synthesis.implementation"
                        options: [
                            { text: "Local", value: "piper" },
                            { text: "ElevenLabs API", value: "elevenlabs" }
                        ]
                        defaultValue: "piper"
                    }

                    SettingsTextInput {
                        visible: synthesisImplementation.selectedValue === "elevenlabs"
                        title: "ElevenLabs Base URL"
                        configKey: "synthesis.elevenlabs_base_url"
                        defaultValue: "wss://api.elevenlabs.io/"
                    }

                    SettingsTextInput {
                        visible: synthesisImplementation.selectedValue === "elevenlabs"
                        title: "ElevenLabs Voice ID"
                        configKey: "synthesis.elevenlabs_voice_id"
                        defaultValue: "21m00Tcm4TlvDq8ikWAM"
                    }

                    SettingsTextInput {
                        visible: synthesisImplementation.selectedValue === "piper"
                        title: "Piper Base URL"
                        configKey: "synthesis.piper_base_url"
                        defaultValue: "http://localhost:5000/"
                    }

                    SettingsTextInput {
                        visible: synthesisImplementation.selectedValue === "piper"
                        title: "Piper Base URL"
                        configKey: "synthesis.piper_voice"
                        defaultValue: "en_US-ljspeech-high.onnx"
                    }
                }
            }
        }
    }
}
