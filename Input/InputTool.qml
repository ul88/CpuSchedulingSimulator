import QtQuick
import QtQuick.Controls

Row {
    required property string text
    required property int inputArea
    required property int validatorTo
    required property int validatorFrom
    Text{
        width: 200
        text: parent.text
        font.pointSize: 15
    }
    TextField {
        text: parent.inputArea.toString()
        font.pointSize: 15
        background: Rectangle {
                implicitWidth: 80
                implicitHeight: 20
                border.color: "#21be2b"
            }
        onTextChanged:{
            parent.inputArea = Number(text)
        }
        validator: IntValidator{bottom:validatorTo; top:validatorFrom}
    }
}
