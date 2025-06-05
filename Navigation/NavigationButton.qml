import QtQuick

Rectangle {
    id: nav1
    width: parent.width
    height: 65
    color: "#7d8597"
    radius: 30
    property string buttonText: "";
    property alias mouseArea: mouseArea

    Text {
        color: "#ffffff"
        text: parent.buttonText
        anchors.fill: parent
        font.pixelSize: 26
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.styleName: "Bold"
        font.bold: true
        font.weight: Font.Bold
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    states:[
        State{
            name: "hovered"; when: mouseArea.containsMouse
            PropertyChanges { target: nav1; color: "#7d8597"; }
        },
        State{
            name: "unHovered"; when: !mouseArea.containsMouse
            PropertyChanges { target: nav1; color: "#6e7e97"; }
        }
    ]

    transitions: [
        Transition {
            from: "hovered"
            to: "unHovered"
            ColorAnimation { target: nav1; duration: 100}
        },
        Transition {
            from: "unHovered"
            to: "hovered"
            ColorAnimation { target: nav1; duration: 100}
        }
    ]
}
