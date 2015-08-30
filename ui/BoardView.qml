import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0

Item {
    id: root
    property var board
    property real nodeDistance: background.width / board.columns
    property bool nodeView: false

    PointView {
        id: pointView
        width: root.width
        height: root.height / 15
        anchors.top: root.top
        anchors.verticalCenter: root.verticalCenter
        players: board.players
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"

        Repeater {
            id: monsterRepeater
            model: board.monsteres
            delegate: MonsterItem {
                monster: model
                nodeDistance: root.nodeDistance
                pressed: boardArea.pressed
            }
        }

        MouseArea {
            id: boardArea
            anchors.fill: parent
            onPressed: {
                board.resetSelections()
            }

            onReleased: {
                for (var i = 0; i < board.monsterCount; i ++){
                    var monsterItem = monsterRepeater.itemAt(i)
                    var dx = (monsterItem.x + monsterItem.width / 2) - boardArea.mouseX
                    var dy = (monsterItem.y + monsterItem.width / 2) - boardArea.mouseY
                    var l = Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2)) - monsterItem.width / 2 - nodeDistance
                    if (l < nodeDistance) {
                        board.evaluateReleased(monsterItem.monster.id)
                    }
                }
                board.resetSelections()
            }

            onMouseXChanged: updateMouseLogic()
            onMouseYChanged: updateMouseLogic()

            function updateMouseLogic() {
                for (var i = 0; i < board.monsterCount; i ++){
                    var monsterItem = monsterRepeater.itemAt(i)
                    var dx = (monsterItem.x + monsterItem.width / 2) - boardArea.mouseX
                    var dy = (monsterItem.y + monsterItem.width / 2) - boardArea.mouseY
                    var l = Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2)) - monsterItem.width / 2 - nodeDistance
                    if (l < nodeDistance) {
                        board.evaluateHovered(true, monsterItem.monster.id);
                    } else {
                        board.evaluateHovered(false, monsterItem.monster.id);
                    }
                }
            }

        }

        SelectorItem {
            id: selectorItem
            nodeDistance: root.nodeDistance
            pressed: boardArea.pressed
            x: boardArea.mouseX - root.nodeDistance * 2.5
            y: boardArea.mouseY - root.nodeDistance * 2.5
            visible: boardArea.pressed

            Repeater {
                id: selectorLineRepeater
                model: board.monsteres
                delegate: Canvas {

                }
            }

        }


    }
}

