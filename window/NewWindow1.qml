pragma ComponentBehavior: Bound

import QtQuick
import CpuSchedulingSimulator 1.0
import QtQuick.Controls.Windows
import QtQuick.Dialogs
import QtQuick.Window 2.15
import "../listcomponent"

Rectangle {
    id: root
    radius: 10
    anchors.fill: parent

    property int cellSize: 117;
    property int editIndex
    property var editProcess

    function errorPasing(error){
        let str = ""
        console.log(error)
        if(error & 32){
            str += "이미 있는 pid 입니다.\n"
        }
        if(error & 16){
            str += "pid는 1~100까지의 수만 가능합니다.\n"
        }
        if(error & 8){
            str += "도착 시간은 0~1000까지의 수만 가능합니다.\n"
        }
        if(error & 4){
            str += "서비스 시간은 0~1000까지의 수만 가능합니다.\n"
        }
        if(error & 2){
            str += "우선순위는 0~10까지의 수만 가능합니다.\n"
        }
        if(error & 1){
            str += "타임 슬라이스는 1~100까지의 수만 가능합니다.\n"
        }
        str += "다시 입력해주세요.\n"
        return str
    }


    NavigationButton{
        id: createButton
        width: 180
        buttonText: "프로세스 생성"
        mouseArea.onClicked: {
            listView.opacity = 0
            createButton.opacity = 0
            addProcessLoader.sourceComponent = addProcessComponenet
        }
    }

    ListModel{
        id: headerModel
        ListElement {t: "pid"}
        ListElement {t: "도착 시간"}
        ListElement {t: "서비스 시간"}
        ListElement {t: "우선순위"}
        ListElement {t: "타임 슬라이스"}
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

        header: HeaderComponent{rectHeight: 60; rectWidth: listView.width; cellSize: root.cellSize; listModel: headerModel}

        delegate: ViewDelegate {
            required property int index;
            rectWidth: listView.width;
            rectHeight: 40;
            onEditProcessSignal: {
                listView.opacity = 0
                createButton.opacity = 0
                editProcess = schedulingManager.getProcessList().getElement(index)
                editIndex = index;
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

    Loader { id: addProcessLoader; anchors.horizontalCenter: root.horizontalCenter; y: 100; width:280; height: 380 }

    Loader { id: changeProcessLoader; anchors.horizontalCenter: root.horizontalCenter; y: 100; width:280; height: 380 }

    Component{
        id: addProcessComponenet
        ProcessInput{
            id: addProcess
            anchors.fill: root
            t: "생성"
            onEdit: {
                let error = schedulingManager.getProcessList().append(process.pcolor, process.pid,
                                                          process.arrivalTime, process.serviceTime,
                                                          process.priority, process.timeSlice);
                if(error){
                    dialog.text = errorPasing(error)
                    dialog.open()
                    return
                }

                listView.opacity = 1
                createButton.opacity = 1
                addProcessLoader.sourceComponent = undefined
            }
            onBack:{
                listView.opacity = 1
                createButton.opacity = 1
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
            t: "수정"

            onEdit: {
                let error = schedulingManager.getProcessList().change(editIndex, process.pcolor, process.pid,
                                                          process.arrivalTime, process.serviceTime,
                                                          process.priority, process.timeSlice);
                if(error){
                    dialog.text = errorPasing(error)
                    dialog.open()
                    return
                }
                listView.opacity = 1
                createButton.opacity = 1
                changeProcessLoader.sourceComponent = undefined
            }

            onBack:{
                listView.opacity = 1
                createButton.opacity = 1
                changeProcessLoader.sourceComponent = undefined
            }
        }
    }

    MessageDialog {
        id: dialog
        buttons: MessageDialog.Ok
    }
}
