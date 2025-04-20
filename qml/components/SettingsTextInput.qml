import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: root
    Layout.fillWidth: true
    spacing: 10

    property string title: "URL"
    property string configKey: "setting.key"
    property string defaultValue: "value"

    Text {
        text: title
        font.pixelSize: 18
        font.weight: Font.Medium
        color: "#e0e5ea"
    }

    Rectangle {
        Layout.preferredHeight: 36
        Layout.preferredWidth: 280
        color: "#1a1d21"
        border.color: "#40454a"
        border.width: 1
        radius: 4

        TextInput {
            id: textInput
            anchors.fill: parent
            anchors.margins: 8
            verticalAlignment: TextInput.AlignVCenter
            color: "#e0e5ea"
            font.pixelSize: 16
            clip: true
            text: root.defaultValue

            onTextEdited: {
                backend.setConfig(root.configKey + "=" + text)
            }
        }
    }

    function updateText(configLine) {
        if (configLine.startsWith(root.configKey + "=")) {
            let value = configLine.split("=")[1]
            textInput.text = value
        }
    }

    Component.onCompleted: {
        backend.configUpdateReceived.connect(updateText)
    }
}
