import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Column {
    id: wakeWordControl
    spacing: 25
    property bool enabled: true

    Text {
        text: "Wake Word"
        font.pixelSize: 24
        font.weight: Font.Medium
        color: "#e0e5ea"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Switch {
        id: wakeWordToggle
        anchors.horizontalCenter: parent.horizontalCenter
        checked: wakeWordControl.enabled

        indicator: Rectangle {
            width: 80
            height: 40
            radius: 40
            color: wakeWordToggle.checked ? "#28a745" : "#555b61"

            Rectangle {
                width: 32
                height: 32
                radius: 16
                color: wakeWordToggle.checked ? "#ffffff" : "#cfd4d9"
                x: wakeWordToggle.checked ? parent.width - width - 4 : 4
                y: 4

                layer.enabled: true
                layer.effect: DropShadow {
                    horizontalOffset: 0
                    verticalOffset: 2
                    radius: 4
                    samples: 8
                    color: Qt.rgba(0, 0, 0, 0.3)
                }

                Behavior on x {
                    NumberAnimation {
                        duration: 400
                        easing.type: Easing.OutCubic
                    }
                }
            }
        }

        onToggled: {
            wakeWordControl.enabled = checked
            backend.setConfig("recording.wake_word_enabled=" + (checked ? "true" : "false"))
        }
    }

    function updateEnabled(configLine) {
        if (configLine.startsWith("recording.wake_word_enabled=")) {
            let value = configLine.split("=")[1]
            wakeWordControl.enabled = (value === "true")
            wakeWordToggle.checked = wakeWordControl.enabled
        }
    }

    Component.onCompleted: {
        backend.configUpdateReceived.connect(updateEnabled)
    }
}
