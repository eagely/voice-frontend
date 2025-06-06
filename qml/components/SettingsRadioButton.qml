import QtQuick
import QtQuick.Controls

RadioButton {
    id: radioButton
    property string configValue: ""

    indicator: Rectangle {
        implicitWidth: 22
        implicitHeight: 22
        x: radioButton.leftPadding
        y: parent.height / 2 - height / 2
        radius: width / 2
        border.color: radioButton.checked ? "#007bff" : "#a0a5ac"
        border.width: 2
        color: "transparent"

        Rectangle {
            width: 12
            height: 12
            x: 5
            y: 5
            radius: width / 2
            color: radioButton.checked ? "#007bff" : "transparent"
            visible: radioButton.checked
        }
    }

    contentItem: Text {
        text: radioButton.text
        font.pixelSize: 16
        leftPadding: radioButton.indicator.width + 10
        verticalAlignment: Text.AlignVCenter
        color: "#e0e5ea"
    }
}
