import QtQuick 2.2
import MonsterWars 1.0

Item {
    id: root
    property QtObject player

    Rectangle {
        anchors.fill: parent
        opacity: 0.8
        color: player.color
        radius: root.height / 3
        Text {
            anchors.centerIn: parent
            text: player.pointCount + " | " + player.percentage * 100 + "%"
            font.bold: true
            font.pixelSize: root.height / 2
        }
    }
}
