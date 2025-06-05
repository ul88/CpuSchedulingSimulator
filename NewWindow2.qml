import QtQuick
import CpuSchedulingSimulator 1.0
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    radius: 10
    Column{
        x: 50
        y: 50
        width: 590
        height: 380
        spacing: 10
        GridLayout{
            anchors.right: parent.right
            columns: 10
            rowSpacing: 5
            Repeater{
                model: schedulingManager.getProcessList()
                delegate: Row{
                    required property int pid
                    required property color pcolor
                    Label {text: pid; font.pixelSize: 15; anchors.verticalCenter: parent.verticalCenter;}
                    Rectangle{
                        width: 25
                        height: 25
                        radius: 10
                        color: pcolor;
                    }
                }
            }
        }
        Rectangle{
            width: parent.width
            height: 100
            border.color: "black"
            border.width: 3
            Flickable {
                id: flick
                width: parent.width - 20
                height: parent.height - 20
                anchors.centerIn: parent
                clip: true
                contentWidth: row.width
                Row{
                    id: row
                    anchors.verticalCenter: parent.verticalCenter
                    Repeater{
                        id:repeater
                        model: schedulingManager.getGanttChart(qsTr("SJF"));
                        delegate: Rectangle{
                            width: (end-start)*10
                            height: 50
                            x: start*15 + 5
                            color: pcolor;
                            border.color: "black"
                            border.width: 2
                            ToolTip.visible: mouse.containsMouse
                            ToolTip.text: qsTr("pid: " + pid + "\n" + "start: " + start + "\n" + "end: " + end)
                            MouseArea{ id: mouse; anchors.fill: parent; hoverEnabled: true; }
                        }
                    }
                }
                ScrollBar.horizontal: ScrollBar { hoverEnabled: true; policy: ScrollBar.AlwaysOn;}
            }

        }
    }
}
