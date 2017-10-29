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

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import MonsterWars 1.0

Page {
    id: root

    Component.onDestruction: {
        console.log("BoardView about to be destroyed. Stopping game")
        gameEngine.stopGame()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: topBar
            Layout.fillWidth: true
            Layout.preferredHeight: app.unitSize * 3
            color: "black"
            RowLayout {
                anchors.fill: parent

                Text {
                    id: gameTime
                    text: gameEngine.displayGameTime
                    Layout.alignment: Qt.AlignVCenter
                    color: "white"
                    style: Text.Outline
                    styleColor: "steelblue"
                    font.bold: true
                    font.pixelSize: app.unitSize * 2
                }

                ScoreView {
                    id: pointView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    players: gameEngine.board.players
                }
            }
        }

        Rectangle {
            id: background
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: "black"

            Image {
                id: backgroundImage
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                sourceSize: Qt.size(parent.width, 0)
                source: Qt.resolvedUrl(dataDirectory + "/levels/level" + gameEngine.board.levelId + "/background.jpg")
            }

            Repeater {
                id: monsterRepeater
                model: gameEngine.board.monsters
                delegate: MonsterItem {
                    monsterValue: model.monsterValue
                    monsterId: model.monsterId
                    monsterColor: model.monsterColor
                    monsterSize: model.monsterSize
                    monsterType: model.monsterType
                    positionX: (background.width - (app.unitSize * gameEngine.columns)) / 2 + model.positionX * app.unitSize
                    positionY: (background.height - (app.unitSize * gameEngine.rows)) / 2 + model.positionY * app.unitSize
                    selected: model.selected
                    pressed: boardArea.pressed
                    lineWidth: selectorItem.lineWidth
                    cellSize: app.unitSize
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
                        var l = Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2)) - monsterItem.width / 2 - app.unitSize
                        if (l < app.unitSize) {
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
                        var l = Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2)) - monsterItem.width / 2 - app.unitSize
                        if (l < app.unitSize) {
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
                anchors.leftMargin: width / 2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: width / 2
                width: app.unitSize * 4
                height: width
                color: "transparent"
                opacity: 0.6
                radius: 1

                Image {
                    id: pauseIcon
                    anchors.fill: parent
                    source: dataDirectory + "/images/pause.png"
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
                pressed: boardArea.pressed
                size: app.unitSize * 6
                lineWidth: app.unitSize / 2
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
                            var xMonster = monsterItem.positionX
                            var yMonster = monsterItem.positionY
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
                    speed: model.speed
                    value: model.value
                    pillowId: model.id
                    colorString: model.colorString
                    absolutSourceX: model.sourceX
                    absolutSourceY: model.sourceY
                    absolutDestinationX: model.destinationX
                    absolutDestinationY: model.destinationY
                    sourceX: (background.width - (cellSize * gameEngine.columns)) / 2 + model.sourceX * app.unitSize
                    sourceY: (background.height - (cellSize * gameEngine.rows)) / 2 + model.sourceY * app.unitSize
                    destinationX: (background.width - (cellSize * gameEngine.columns)) / 2 + model.destinationX * app.unitSize
                    destinationY: (background.height - (cellSize * gameEngine.rows)) / 2 + model.destinationY * app.unitSize
                    cellSize: app.unitSize
                }
            }
        }

    }
    Connections {
        target: Qt.application
        onActiveChanged: {
            if (!Qt.application.active && gameEngine.running)  {
                pauseMenu.visible = true
                gameEngine.pauseGame()
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
