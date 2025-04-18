import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root
    Layout.fillWidth: true
    spacing: 10

    property string title: "Setting Group"
    property var options: [
        { text: "Option 1", value: "option1" },
        { text: "Option 2", value: "option2" }
    ]
    property string configKey: "setting.key"
    property string defaultValue: options.length > 0 ? options[0].value : ""

    property bool updatingFromServer: false

    Text {
        text: title
        font.pixelSize: 18
        font.weight: Font.Medium
        color: "#e0e5ea"
    }

    ButtonGroup {
        id: buttonGroup
        onCheckedButtonChanged: {
            if (checkedButton && !root.updatingFromServer) {
                let configString = root.configKey + "=" + checkedButton.configValue
                backend.setConfig(configString)
            }
        }
    }

    RowLayout {
        spacing: 16

        Repeater {
            id: radioRepeater
            model: options

            SettingsRadioButton {
                text: modelData.text
                configValue: modelData.value
                ButtonGroup.group: buttonGroup
                checked: modelData.value === root.defaultValue
            }
        }
    }

    function updateSelectedButton(configLine) {
        if (configLine.startsWith(root.configKey + "=")) {
            let value = configLine.split("=")[1]
            root.updatingFromServer = true
            for (let i = 0; i < radioRepeater.count; ++i) {
                let btn = radioRepeater.itemAt(i)
                btn.checked = (btn.configValue === value)
            }
            root.updatingFromServer = false
        }
    }

    Component.onCompleted: {
        backend.configUpdateReceived.connect(updateSelectedButton)
    }
}
