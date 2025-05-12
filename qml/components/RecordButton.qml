import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Button {
    id: recordButton
    width: 150
    height: 150
    property bool recording: false

    background: Rectangle {
        radius: width / 2
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#007bff" }
            GradientStop { position: 1.0; color: "#0056b3" }
        }

        layer.enabled: true
        layer.effect: DropShadow {
            horizontalOffset: 0
            verticalOffset: 6
            radius: 15
            samples: 15
            color: Qt.rgba(0, 123, 255, 0.3)
        }
    }

    contentItem: Text {
        text: "\uf130"
        font.family: "FontAwesome"
        font.pixelSize: 60
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    onClicked: {
        recording = !recording
        if(recording) backend.startRecording()
        else backend.stopRecording()
    }

    transitions: Transition {
        PropertyAnimation {
            properties: "transform,verticalOffset,radius,color"
            duration: 300
            easing.type: Easing.OutCubic
        }
    }
}
