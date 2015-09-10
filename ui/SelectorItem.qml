import QtQuick 2.0
import MonsterWars 1.0

Item{
    id: root
    property real nodeDistance
    property real lineWidth
    property real size
    property bool pressed
    Rectangle {
        id: selector
        width: size
        height: width
        color: "steelblue"
        border.color: "steelblue"
        border.width: lineWidth
        radius: width / 2
    }
}
