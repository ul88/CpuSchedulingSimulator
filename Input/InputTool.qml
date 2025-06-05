import QtQuick
import QtQuick.Controls

Row {
    required property string text
    required property int inputArea
    Text{
        text: parent.text
        font.pointSize: 20
    }
    TextField {
        text: parent.inputArea.toString()
        font.pointSize: 20
        background: Rectangle {
                implicitWidth: 50
                implicitHeight: 20
                border.color: "#21be2b"
            }
        onTextChanged:{
            parent.inputArea = Number(text)
        }
    }
}
