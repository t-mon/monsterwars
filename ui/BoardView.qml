/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Monster Wars.                                     *
 *                                                                         *
 *  Monster Wars is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Monster Wars is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Monster Wars. If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

import QtQuick 2.2
import MonsterWars 1.0

Item {
    id: root
    property real nodeDistance: (background.width - units.gu(3)) / gameEngine.board.columns

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    Row {
        id: topBar
        width: root.width
        height: units.gu(3)
        anchors.top: root.top
        anchors.horizontalCenter: root.horizontalCenter

        Rectangle {
            height: parent.height
            width: units.gu(8)
            color: "black"
            Text {
                id: gameTime
                anchors.fill: parent
                anchors.centerIn: parent
                anchors.left: parent.left
                anchors.leftMargin: units.gu(1)
                text: gameEngine.displayGameTime
                color: "white"
                style: Text.Outline
                styleColor: "steelblue"
                font.bold: true
                font.pixelSize: parent.height * 4 / 5
            }

        }

        PointView {
            id: pointView
            width: parent.width - gameTime.width
            height: parent.height
            players: gameEngine.board.players
        }
    }

    Rectangle {
        id: background
        width: root.width
        height: root.height - topBar.height
        anchors.top: topBar.bottom
        anchors.horizontalCenter: root.horizontalCenter
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:///backgrounds/background2.jpg"
        }

            Repeater {
                id: monsterRepeater
                model: gameEngine.board.monsters
                delegate: MonsterItem {
                    nodeDistance: root.nodeDistance
                    monsterValue: model.monsterValue
                    monsterId: model.monsterId
                    monsterColor: model.monsterColor
                    monsterSize: model.monsterSize
                    monsterType: model.monsterType
                    positionX: model.positionX
                    positionY: model.positionY
                    selected: model.selected
                    pressed: boardArea.pressed
                    lineWidth: selectorItem.lineWidth
                }
            }

        MouseArea {
            id: boardArea
            anchors.fill: parent
            onPressed: gameEngine.board.resetSelections()
            onReleased: {
                for (var i = 0; i < gameEngine.board.monsterCount; i ++){
                    var monsterItem = monsterRepeater.itemAt(i)
                    var dx = (monsterItem.x + monsterItem.width / 2) - boardArea.mouseX
                    var dy = (monsterItem.y + monsterItem.width / 2) - boardArea.mouseY
                    var l = Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2)) - monsterItem.width / 2 - nodeDistance
                    if (l < nodeDistance) {
                        gameEngine.board.evaluateReleased(monsterItem.monsterId)
                    }
                }
                gameEngine.board.resetSelections()
            }

            onMouseXChanged: {
                updateMouseLogic()
                selectorLines.requestPaint()
            }
            onMouseYChanged: {
                updateMouseLogic()
                selectorLines.requestPaint()
            }

            function updateMouseLogic() {
                for (var i = 0; i < gameEngine.board.monsterCount; i ++){
                    var monsterItem = monsterRepeater.itemAt(i)
                    var dx = (monsterItem.x + monsterItem.width / 2) - boardArea.mouseX
                    var dy = (monsterItem.y + monsterItem.width / 2) - boardArea.mouseY
                    var l = Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2)) - monsterItem.width / 2 - nodeDistance
                    if (l < nodeDistance) {
                        gameEngine.board.evaluateHovered(true, monsterItem.monsterId);
                    } else {
                        gameEngine.board.evaluateHovered(false, monsterItem.monsterId);
                    }
                }
            }
        }

        Rectangle {
            id: pauseButton
            anchors.left: parent.left
            anchors.leftMargin: units.gu(2)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(2)
            width: units.gu(5)
            height: units.gu(5)
            color: "transparent"
            radius: units.gu(1)

            Image {
                id: pauseIcon
                anchors.fill: parent
                source: "qrc:///images/pause.png"
            }

            MouseArea {
                id: pauseButtonMouseArea
                anchors.fill: pauseButton
                onClicked: {
                    pauseMenu.visible = true
                    gameEngine.pauseGame()
                }
            }
        }

        SelectorItem {
            id: selectorItem
            nodeDistance: root.nodeDistance
            pressed: boardArea.pressed
            size: nodeDistance * 6
            lineWidth: nodeDistance / 2
            x: boardArea.mouseX - size / 2
            y: boardArea.mouseY - size / 2
            visible: boardArea.pressed && gameEngine.running
        }

        Canvas {
            id: selectorLines
            anchors.fill: parent
            smooth: true
            visible: selectorItem.visible

            onPaint: {
                var ctx = selectorLines.getContext('2d')
                var offset = 0;
                ctx.save();
                ctx.reset();
                for (var i = 0; i < gameEngine.board.monsterCount; i ++) {
                    var monsterItem = monsterRepeater.itemAt(i)
                    if (monsterItem.selected) {
                        var xMonster = monsterItem.positionX * root.nodeDistance
                        var yMonster = monsterItem.positionY * root.nodeDistance
                        var xSelector = selectorItem.x + selectorItem.size / 2
                        var ySelector = selectorItem.y + selectorItem.size / 2

                        var alpha = Math.atan2(ySelector - yMonster, xSelector - xMonster)

                        var xMonsterNew = xMonster + monsterItem.width / 2 * Math.cos(alpha)
                        var yMonsterNew = yMonster + monsterItem.width / 2 * Math.sin(alpha)

                        ctx.moveTo(xMonsterNew, yMonsterNew)
                        ctx.lineTo(xSelector, ySelector)
                        ctx.lineWidth = selectorItem.lineWidth
                        ctx.lineCap = "round"
                        ctx.strokeStyle = "steelblue"
                        ctx.stroke()
                    }
                }
                ctx.restore();
            }
        }


        Repeater {
            id: attackPillows
            model: gameEngine.pillows
            delegate: AttackPillowItem {
                nodeDistance: root.nodeDistance
                speed: model.speed
                value: model.value
                pillowId: model.id
                colorString: model.colorString
                sourceX: model.sourceX
                sourceY: model.sourceY
                destinationX: model.destinationX
                destinationY: model.destinationY
            }
        }
    }

    PauseMenu {
        id: pauseMenu
        anchors.fill: parent
    }

    GameOverView {
        id: gameOverView
        anchors.fill: parent
    }

    Connections {
        target: gameEngine
        onGameOver: gameOverView.visible = true
    }
}
