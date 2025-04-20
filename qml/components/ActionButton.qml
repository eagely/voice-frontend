import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Button {
    id: actionButton

    property bool isPrimary: true
    property color primaryStartColor: "#007bff"
    property color primaryEndColor: "#0056b3"
    property color secondaryColor: "#555b61"
    property color secondaryBorderColor: "#40454a"

    background: Rectangle {
        radius: 8

        color: isPrimary ? "transparent" : secondaryColor
        border.color: isPrimary ? "transparent" : secondaryBorderColor
        border.width: isPrimary ? 0 : 1

        layer.enabled: isPrimary && actionButton.enabled
        layer.effect: DropShadow {
            horizontalOffset: 0
            verticalOffset: 2
            radius: 8
            samples: 16
            color: Qt.rgba(0, 0, 0, 0.3)
        }
    }

    contentItem: Text {
        text: actionButton.text
        font.pixelSize: 16
        font.weight: Font.Medium
        color: isPrimary ? (actionButton.enabled ? "#ffffff" : "#a0a5ac") : "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
