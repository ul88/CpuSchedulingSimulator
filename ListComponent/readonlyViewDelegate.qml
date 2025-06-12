import QtQuick

Rectangle{
    id: rowRectangle
    required property color pcolor;
    required property int pid;
    required property int waitTime;
    required property int responseTime;
    required property int turnAroundTime;
    required property int rectWidth
    required property int rectHeight
    property int cellSize: 117
    property alias mouseArea: mouseArea
    property int fontSize: 15
    signal editProcessSignal/*(color pcolor, int pid, int arrivalTime, int serviceTime, int priority, int timeSlice)*/

    width: rectWidth + 50
    height: rectHeight // 25

    MouseArea{
        id: mouseArea
        anchors.fill: rowRectangle
        hoverEnabled: true
    }

    states:[
        State{
            name: "hovered"; when: mouseArea.containsMouse
            PropertyChanges { target: rowRectangle; color: "#f1f3f5"; }
        },
        State{
            name: "unHovered"; when: !mouseArea.containsMouse
            PropertyChanges { target: rowRectangle; color: "#ffffff"; }
        }
    ]

    Row{
        id: row
        anchors.fill: rowRectangle
        Rectangle{ width:25; height:25; color: rowRectangle.pcolor; radius: 10; anchors.verticalCenter: parent.verticalCenter}
        Text{ width: cellSize-25; height: rowRectangle.height; text: rowRectangle.pid; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.waitTime; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.responseTime; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.turnAroundTime; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
    }
}
