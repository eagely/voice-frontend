import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: root
    Layout.fillWidth: true
    spacing: 10

    property string title: "Settings Group"
    property var options: [
        { text: "Option 1", value: "option1" },
        { text: "Option 2", value: "option2" }
    ]
    property string configKey: "setting.key"
    property string defaultValue: options.length > 0 ? options[0].value : ""
    property string selectedValue: defaultValue
    
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
                root.selectedValue = checkedButton.configValue
                backend.setConfig(root.configKey + "=" + checkedButton.configValue)
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
            root.selectedValue = value
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
