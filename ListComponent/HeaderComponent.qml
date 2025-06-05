import QtQuick


Rectangle{
    id: headerRect
    required property int cellSize
    required property int rectWidth;
    required property int rectHeight;
    property int fontSize: 15
    width: rectWidth
    height: rectHeight
    border.color: "black"
    border.width: 1
    z: 2
    Row{
        Text{
            width: cellSize
            height: headerRect.height
            text: "pid"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignBottom
        }
        Text{
            width: cellSize
            height: headerRect.height
            text: "도착 시간"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignBottom
        }
        Text{
            width: cellSize
            height: headerRect.height
            text: "서비스 시간"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignBottom
        }
        Text{
            width: cellSize
            height: headerRect.height
            text: "우선순위"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignBottom
        }
        Text{
            width: cellSize
            height: headerRect.height
            text: "타임 슬라이스"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignBottom
        }
    }
}
