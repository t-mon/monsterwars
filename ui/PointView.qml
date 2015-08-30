import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0

Item {
    id: root
    property var players
    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
    }

    Row {
        id: pointRow
        Repeater {
            model: players
            delegate: ScoreBar {
                player: model
                height: root.height
                anchors.topMargin: root.height / 10
                anchors.bottomMargin: root.height / 10
                width: root.width * model.percentage
            }
        }
    }
}

