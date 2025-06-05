import QtQuick
import CpuSchedulingSimulator 1.0
import QtQuick.Controls.Material

Rectangle{
    id: rowRectangle
    required property color pcolor;
    required property int pid;
    required property int arrivalTime;
    required property int serviceTime;
    required property int priority;
    required property int timeSlice;
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
        onClicked: {
            if(rowImage.x >= cellSize+5) rowImage.x = cellSize - 55
            else rowImage.x = cellSize+5
        }
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
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.arrivalTime; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.serviceTime; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.priority; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
        Item{
            width: cellSize
            height: rowRectangle.height
            Text{ width: cellSize; height: rowRectangle.height; text: rowRectangle.timeSlice; font.pixelSize: rowRectangle.fontSize; verticalAlignment: Text.AlignVCenter;}
            Row{
                id: rowImage
                anchors.verticalCenter: parent.verticalCenter
                x: cellSize+5
                Behavior on x{ NumberAnimation{} }
                Image{
                    source: "qrc:/edit_icon.png"
                    anchors.verticalCenter: rowImage.verticalCenter
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("edit clicked")
                            editProcessSignal() //(pcolor, pid, arrivalTime, serviceTime, priority, timeSlice)
                        }
                    }
                }
                Image{
                    source: "qrc:/delete_icon.png"
                    anchors.verticalCenter: rowImage.verticalCenter
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("delete clicked " + rowRectangle.pid)
                            schedulingManager.getProcessList().remove(rowRectangle.pid);
                        }
                    }
                }
            }
        }

    }
}
