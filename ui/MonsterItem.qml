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
    property int monsterValue
    property int monsterId
    property string monsterType
    property string monsterColor
    property int monsterSize
    property int positionX
    property int positionY
    property bool selected
    property bool pressed
    property real lineWidth

    width: monsterSize * boardView.cellSize * 2
    height: width
    x: positionX - width / 2
    y: positionY - width / 2

    Rectangle {
        id: monsterArea
        anchors.fill: parent
        radius: width / 2
        color: "transparent"

        Rectangle {
            id: monsterItem
            anchors.fill: parent
            color: "transparent"
            radius: width / 2

            SequentialAnimation {
                ScaleAnimator {
                    target: imageSprite
                    from: 0.98
                    to: 1.03
                    easing.type: Easing.Linear;
                    duration: 500
                }
                ScaleAnimator {
                    target: imageSprite
                    from: 1.03
                    to: 0.98
                    easing.type: Easing.Linear;
                    duration: 800
                }
                running: true
                loops: Animation.Infinite
            }

            Loader {
                id: imageSprite
                anchors.fill: monsterItem
                anchors.centerIn: monsterItem

                property string monsterSource: "qrc:///monsters/monster-" + monsterType + "-" + monsterColor + ".png"

                Binding {
                    target: imageSprite.item
                    property: "source"
                    value: imageSprite.monsterSource
                }

                onMonsterSourceChanged: {
                    imageSprite.sourceComponent = null
                    imageSprite.sourceComponent = spriteComponent
                }
            }

            Component {
                id: spriteComponent

                SpriteSequence {
                    property alias source: sprite.source
                    interpolate: true
                    goalSprite: "still"

                    Sprite{
                        id: sprite
                        name: "still"
                        frameCount: 6
                        frameWidth: 200
                        frameHeight: 200
                        frameDuration: 110
                    }
                }
            }

            Rectangle {
                id: valueRectangle
                anchors.bottom: parent.bottom
                anchors.bottomMargin: - boardView.cellSize / 2
                anchors.right: parent.right
                anchors.rightMargin: - boardView.cellSize / 2
                width: boardView.cellSize * 4
                height: boardView.cellSize * 3
                color: "transparent"
//                color: "black"
//                opacity: 0.8
//                border.color: "gray"
                radius: width / 4
                visible: monsterValue != 0

                Image {
                    id: valuePillow
                    source: "qrc:///monsters/pillow.png"
                    anchors.fill: parent
                }

                Text {
                    id: valueLabel
                    anchors.centerIn: parent
                    visible: monsterValue == 0 ? false : true
                    text: monsterValue
                    font.weight: Font.DemiBold
                    style: Text.Outline
                    styleColor: "black"
                    font.pixelSize: boardView.cellSize * 2
                    color: monsterColor == "green" ? app.green : monsterColor == "red" ? app.red : monsterColor == "blue" ? app.blue : "white"
                }
            }

            Rectangle {
                id: descriptionRectangle
                visible: false
                width: 8.5 * boardView.cellSize
                height: 3.5 * boardView.cellSize
                radius: boardView.cellSize
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.top
                anchors.bottomMargin: boardView.cellSize / 2
                color: "#804682b4"
                border.color: "Black"

                Text {
                    id: descriptionText
                    visible: parent.visible
                    anchors.centerIn: descriptionRectangle
                    text: "id = " + monsterId + "\n" + monsterType
                    style: Text.Outline
                    styleColor: "white"
                    font.pixelSize: boardView.cellSize * 1.3
                    color: "white"
                }
            }

            MouseArea {
                id: monsterMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.AllButtons
                hoverEnabled: true
                onEntered: {
                    descriptionRectangle.visible = !pressed
                }
                onExited: descriptionRectangle.visible = false
            }
        }

        Rectangle {
            id: impactCloud
            opacity: 0
            anchors.centerIn: parent
            width: root.width
            height: width
            color: "transparent"

            Image {
                id: impactCloudImage
                anchors.fill: parent
                source: "qrc:///images/cloud.png"
            }
        }

        ParallelAnimation {
            id: impactAnimation
            running: false
            PropertyAnimation {
                target: impactCloud
                properties: "scale"
                from: 0.4
                to: 0.8
                easing.type: Easing.OutCubic
                duration: 1000
            }
            PropertyAnimation {
                target: impactCloud
                properties: "opacity"
                from: 1
                to: 0
                easing.type: Easing.InQuart
                duration: 900
            }
        }

        Connections {
            target: gameEngine.board.monster(monsterId)
            onImpact: impactAnimation.restart()
        }

        Rectangle {
            id: monsterSelectionCircle
            anchors.fill: parent
            border.color: selected ? "steelblue" : "transparent"
            border.width: lineWidth
            color: "transparent"
            radius: width / 2
        }
    }
}



