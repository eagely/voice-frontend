import QtQuick
import QtQuick.Controls

Button {
    id: settingsButton
    width: 40
    height: 40

    background: null

    contentItem: Text {
        text: "\uf013"
        font.family: "FontAwesome"
        font.pixelSize: 24
        color: settingsButton.hovered ? "#ffffff" : "#a0a5ac"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
