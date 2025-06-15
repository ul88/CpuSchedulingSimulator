import QtQuick
import CpuSchedulingSimulator 1.0
import QtQuick.Controls
import QtQuick.Layouts
import "../listcomponent"

Rectangle {
    id: root
    radius: 10

    property int prevEnd: -1

    property int gap: 15;

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
            height: 140
            border.color: "black"
            border.width: 3
            Flickable {
                id: flick
                width: parent.width - 10
                height: parent.height - 20
                anchors.centerIn: parent
                clip: true
                contentWidth: row.width + 40
                Row{
                    id: row
                    x: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Repeater{
                        id:repeater
                        model: schedulingManager.getGanttChart(comboBox.editText);
                        delegate: Row{
                            Column{
                                id: startLine
                                width: 2
                                Rectangle{
                                    width: parent.width
                                    y: -5
                                    height: 60
                                    color: "black"
                                }
                                Text{
                                    width:parent.width
                                    x:-5
                                    text: start;
                                }
                                Component.onCompleted: {
                                    if(prevEnd == start){
                                        startLine.opacity = 0
                                        startLine.width = 0
                                    }
                                    prevEnd = end
                                }
                            }
                            Rectangle{

                                width: (end-start)*gap
                                height: 50
                                color: pcolor;
                                border.color: "black"
                                border.width: 1
                                ToolTip.visible: mouse.containsMouse
                                ToolTip.text: qsTr("pid: " + (pid ? pid : "X") + "\n" + "start: " + start + "\n" + "end: " + end)
                                MouseArea{ id: mouse; anchors.fill: parent; hoverEnabled: true; }
                            }
                            Column{
                                Rectangle{
                                    width: 2
                                    y: -5
                                    height: 60
                                    color: "black"
                                }
                                Text{
                                    width:2
                                    x:-5
                                    text: end;
                                }
                            }
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
            height: 260
            spacing: 2.5
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            headerPositioning: ListView.OverlayHeader
            snapMode: ListView.SnapToItem
            model: schedulingManager.getOutput(comboBox.editText)
            header: HeaderComponent{rectHeight: 60; rectWidth: listView.width; cellSize:117; listModel: headerModel}
            delegate: ReadonlyViewDelegate{ rectWidth: listView.width; rectHeight: 40; }
            footer: FooterComponent{rectWidth: listView.width; rectHeight: 40;}

            ScrollBar.vertical: ScrollBar{
                id: scrollBar
                minimumSize: 0.1
                width: 8
                y: listView.headerItem.height
                interactive: false
                hoverEnabled: false
                bottomPadding : listView.headerItem.height + 16

                contentItem: Rectangle{
                    implicitWidth: 8
                    radius: 10
                    color: "#6e7e97"
                }

                background: Rectangle{
                    implicitWidth: 8
                    color: "#ffffff"
                }
            }
        }
    }
}
