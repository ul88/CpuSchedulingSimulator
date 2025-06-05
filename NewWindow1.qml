pragma ComponentBehavior: Bound

import QtQuick
import CpuSchedulingSimulator 1.0
import QtQuick.Controls.Windows
import QtQuick.Window 2.15
import "./ListComponent"

Rectangle {
    id: root
    radius: 10

    property int cellSize: 117;
    property int editIndex
    property var editProcess


    NavigationButton{
        id: createButton
        width: 180
        buttonText: "프로세스 생성"
        mouseArea.onClicked: {
            addProcessLoader.sourceComponent = addProcessComponenet
        }
    }

    ListView {
        id: listView
        x: 50
        y: 100
        width: 590
        height: 380
        spacing: 2.5
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        headerPositioning: ListView.OverlayHeader
        snapMode: ListView.SnapToItem
        model: schedulingManager.getProcessList()

        header: HeaderComponent{rectHeight: 60; rectWidth: listView.width; cellSize: root.cellSize}

        delegate: ViewDelegate {
            required property int index;
            rectWidth: listView.width;
            rectHeight: 40;
            onEditProcessSignal: {
                listView.opacity = 0;
                editProcess = schedulingManager.getProcessList().getElement(index)
                editIndex = index;
            }
        }

        onOpacityChanged: {
            if(opacity == 0){
                changeProcessLoader.sourceComponent = changeProcessComponent
            }
        }

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
        Behavior on opacity { NumberAnimation { duration: 500;} }
    }

    Loader { id: addProcessLoader; x: 50; y: 100; width: 590; height: 380 }

    Loader { id: changeProcessLoader; x: 50; y: 100; width: 590; height: 380 }

    Component{
        id: addProcessComponenet
        ProcessInput{
            id: addProcess
            anchors.fill: parent
            onEdit: {
                schedulingManager.getProcessList().append(process.pcolor, process.pid,
                                                          process.arrivalTime, process.serviceTime,
                                                          process.priority, process.timeSlice);
                listView.opacity = 1
                addProcessLoader.sourceComponent = undefined
            }
        }
    }

    Component{
        id: changeProcessComponent
        ProcessInput{
            id: changeProcess
            anchors.fill: parent
            process: editProcess

            onEdit: {
                schedulingManager.getProcessList().change(editIndex, process.pcolor, process.pid,
                                                          process.arrivalTime, process.serviceTime,
                                                          process.priority, process.timeSlice);
                listView.opacity = 1
                changeProcessLoader.sourceComponent = undefined
            }
        }
    }
}
