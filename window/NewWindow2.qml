import QtQuick
import CpuSchedulingSimulator 1.0
import QtQuick.Controls
import QtQuick.Layouts
import "../listcomponent"

Rectangle {
    id: root
    radius: 10

    ComboBox{
        id: comboBox
        width: 100
        height: 50
        model: ["FCFS", "SJF", "NonpreemptivePriority", "PreemptivePriority", "RR", "SRT", "HRN"]
    }

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
                        model: schedulingManager.getGanttChart(comboBox.editText);
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

        ListModel{
            id: headerModel
            ListElement {t: "pid"}
            ListElement {t: "대기 시간"}
            ListElement {t: "응답 시간"}
            ListElement {t: "반환 시간"}
        }

        ListView{
            id: listView
            width: parent.width
            height: parent.height
            spacing: 2.5
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            headerPositioning: ListView.OverlayHeader
            snapMode: ListView.SnapToItem
            model: schedulingManager.getOutput(comboBox.editText)
            header: HeaderComponent{rectHeight: 60; rectWidth: listView.width; cellSize:117; listModel: headerModel}
            delegate: ReadonlyViewDelegate{ rectWidth: listView.width; rectHeight: 40; }
            footer: FooterComponent{rectWidth: listView.width; rectHeight: 40;}
        }
    }
}
