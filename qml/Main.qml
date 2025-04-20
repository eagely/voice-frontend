import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "components"

ApplicationWindow {
    id: root
    visible: true
    width: 1024
    height: 600

    property bool recording: false
    property bool wakeWordEnabled: true

    color: "#2c3035"

    Item {
        id: mainScreen
        anchors.fill: parent
        visible: !settingsScreen.visible

        SettingsButton {
            id: settingsButton
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 25
            anchors.rightMargin: 25

            onClicked: {
                settingsScreen.visible = true
                mainScreen.visible = false
            }
        }

        Rectangle {
            id: leftSection
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width * 0.45
            color: "transparent"

            RecordButton {
                id: recordButton
                anchors.centerIn: parent
                recording: root.recording

                onClicked: {
                    root.recording = recordButton.recording
                }
            }
        }

        Rectangle {
            id: rightSection
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width * 0.45
            color: "transparent"

            WakeWordToggle {
                anchors.centerIn: parent
                enabled: root.wakeWordEnabled

                onEnabledChanged: {
                    root.wakeWordEnabled = enabled
                }
            }
        }

        ScrollView {
            id: outputScrollView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 150
            visible: false

            TextArea {
                id: output
                readOnly: true
                textFormat: Text.PlainText
                wrapMode: Text.Wrap
                color: "#e0e5ea"
                background: Rectangle {
                    color: "#1a1d21"
                    opacity: 0.8
                }
            }
        }
    }

    Settings {
        id: settingsScreen
        visible: false

        onClosed: {
            settingsScreen.visible = false
            mainScreen.visible = true
        }
    }

    Connections {
        target: backend
        function onTextMessageReceived(message) {
            output.text += message + "\n"
            outputScrollView.visible = true
        }

        function onBinaryMessageReceived(data) {
            audioPlayer.appendAudioData(data)
        }
    }
}
