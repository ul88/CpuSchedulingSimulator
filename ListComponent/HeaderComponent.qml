import QtQuick


Rectangle{
    id: headerRect
    required property int cellSize
    required property int rectWidth;
    required property int rectHeight;
    property int fontSize: 15
    required property ListModel listModel // model에 t 속성 필요
    width: rectWidth
    height: rectHeight
    border.color: "black"
    border.width: 1
    z: 2

    Row{
        Repeater{
            model: listModel
            delegate: Text{
                width: cellSize
                height: headerRect.height
                text: t
                font.pixelSize: fontSize
                verticalAlignment: Text.AlignBottom
            }
        }
    }
}
