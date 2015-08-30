import QtQuick 2.0
import QtGraphicalEffects 1.0
import MonsterWars 1.0

Item{
    id: root
    property real nodeDistance
    property bool pressed
    Rectangle {
        id: selector
        width: nodeDistance * 5
        height: width
        color: "transparent"
        border.color: "steelblue"
        border.width: nodeDistance / 3
        radius: width / 2
    }
}
