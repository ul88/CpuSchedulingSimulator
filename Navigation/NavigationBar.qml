import QtQuick

Column {
    id: column
    width: 200
    height: 560
    spacing: 5
    property int clickedButton;

    NavigationButton {
        id: navigationButton1
        buttonText: "메인화면"
        mouseArea.onClicked: {
            parent.clickedButton = 1;
        }
    }

    NavigationButton {
        id: navigationButton2
        buttonText: "프로세스"
        mouseArea.onClicked: {
            parent.clickedButton = 2;
        }
    }

    NavigationButton {
        id: navigationButton3
        buttonText: "실행"
        mouseArea.onClicked: {
            parent.clickedButton = 3;
        }
    }

    NavigationButton {
        id: navigationButton4
        buttonText: "종료"
        mouseArea.onClicked: {
            Qt.quit()
        }
    }
}
