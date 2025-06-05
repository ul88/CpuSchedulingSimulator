import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import CpuSchedulingSimulator 1.0

Rectangle{

    property var process: ({pcolor: undefined, pid: undefined, arrivalTime: undefined,
                               serviceTime: undefined, priority: undefined, timeSlice: undefined})
    signal edit

    // Component.onCompleted: {
    //     if(!process.pcolor) process.pcolor = ;
    // }

    Column{
        spacing: 5
        ColorDialog {
            id: colorDialog
            title: "색상 선택"
            onAccepted: {
                colorRect.color = selectedColor
            }
        }
        Rectangle{
            id: colorRect
            width: 25
            height: 25
            color: process.pcolor ? process.pcolor : process.pcolor = schedulingManager.getProcessList().getNewColor()
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    colorDialog.open()
                }
            }
            onColorChanged: {
                process.pcolor = color
            }
        }

        InputTool{
            text: "pid"
            inputArea: process.pid ? process.pid : 0
            onInputAreaChanged: {process.pid = inputArea}
        }
        InputTool{
            text: "도착 시간"
            inputArea: process.arrivalTime ? process.arrivalTime : 0
            onInputAreaChanged: {process.arrivalTime = inputArea}
        }
        InputTool{
            text: "서비스 시간"
            inputArea: process.serviceTime ? process.serviceTime : 0
            onInputAreaChanged: {process.serviceTime = inputArea}
        }
        InputTool{
            text: "우선순위"
            inputArea: process.priority ? process.priority : 0
            onInputAreaChanged: {process.priority = inputArea}
        }
        InputTool{
            text: "타임슬라이스"
            inputArea: process.timeSlice ? process.timeSlice : 0
            onInputAreaChanged: {process.timeSlice = inputArea}
        }
        NavigationButton{
            buttonText: "수정"
            mouseArea.onClicked: {
                console.log("수정!")
                edit()
            }
        }
    }

}

