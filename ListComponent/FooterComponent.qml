import QtQuick

Rectangle{
    id: rowRectangle
    property var avg: schedulingManager.getOutput(comboBox.editText).getAvg()
    required property int rectWidth
    required property int rectHeight
    property int cellSize: 117
    property alias mouseArea: mouseArea
    property int fontSize: 15

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
        Text{ width: cellSize; height: rowRectangle.height; text: "평균"; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.avg.avgWaitTime.toFixed(2); font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.avg.avgResponseTime.toFixed(2); font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.avg.avgTurnAroundTime.toFixed(2); font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
    }
}
