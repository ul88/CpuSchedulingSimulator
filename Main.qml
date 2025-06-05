import QtQuick
import QtQuick.Controls
import CpuSchedulingSimulator 1.0

Window {
    id: mainWindow
    width: 970
    height: 560
    visible: true
    color: "#5c677d"
    title: qsTr("Cpu Scheduling Simulator")
    property int clickedButton : navigationBar.clickedButton

    NavigationBar {
        id: navigationBar
        x: 10
        y: 10
        width: 200
        height: 540
    }

    Loader {
        id: newWindowLoader
        x: 220
        y: 10
        width: 740
        height: 540
        source:{
            switch(mainWindow.clickedButton){
            case 2:
                return "NewWindow1.qml";
            case 3:
                schedulingManager.run();
                return "NewWindow2.qml";
            default:
                return "";
            }
        }
    }
}
