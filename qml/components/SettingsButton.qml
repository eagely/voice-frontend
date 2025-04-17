import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: settingsButton
    width: 44
    height: 44

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
