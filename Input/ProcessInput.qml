import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import CpuSchedulingSimulator 1.0

Rectangle{
    required property string t;
    property var process: ({pcolor: undefined, pid: undefined, arrivalTime: undefined,
                               serviceTime: undefined, priority: undefined, timeSlice: undefined})
    signal edit
    signal back
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
            validatorTo: 1
            validatorFrom: 100
        }
        InputTool{
            text: "도착 시간"
            inputArea: process.arrivalTime ? process.arrivalTime : 0
            onInputAreaChanged: {process.arrivalTime = inputArea}
            validatorTo: 0
            validatorFrom: 1000
        }
        InputTool{
            text: "서비스 시간"
            inputArea: process.serviceTime ? process.serviceTime : 0
            onInputAreaChanged: {process.serviceTime = inputArea}
            validatorTo: 1
            validatorFrom: 1000
        }
        InputTool{
            text: "우선순위"
            inputArea: process.priority ? process.priority : 0
            onInputAreaChanged: {process.priority = inputArea}
            validatorTo: 0
            validatorFrom: 10
        }
        InputTool{
            text: "타임슬라이스"
            inputArea: process.timeSlice ? process.timeSlice : 0
            onInputAreaChanged: {process.timeSlice = inputArea}
            validatorTo: 1
            validatorFrom: 100
        }
        Row{
            NavigationButton{
                width: 140
                height: 45
                buttonText: "뒤로가기"
                mouseArea.onClicked: {
                    back()
                }
            }
            NavigationButton{
                width: 140
                height: 45
                buttonText: t
                mouseArea.onClicked: {
                    edit()
                }
            }
        }

    }

}

