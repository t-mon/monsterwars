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
import MonsterWars 1.0

Item {
    id: root
    visible: false
    property real buttonSize: 30

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        opacity: 0.4
        color: "black"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.visible = false
                gameEngine.continueGame()
            }
        }
    }

    Rectangle {
        id: menuRectangle
        color: "black"
        anchors.fill: parent
        anchors.margins: 20
        radius: 10

        Column {
            id: pauseMenuColumn
            anchors.fill: parent

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                color: "transparent"
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    // TRANSLATORS: The "Continue" button in the pause menu
                    text: qsTr("Continue")
                    font.bold: true
                    font.pixelSize: 20
                    color: continueMouseArea.pressed ? "steelblue" : "white"
                }
                MouseArea {
                    id: continueMouseArea
                    anchors.fill: parent
                    onClicked: {
                        root.visible = false
                        gameEngine.continueGame()
                    }
                }
            }

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                color: "transparent"
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    // TRANSLATORS: The "Restart" button in the pause menu
                    text: qsTr("Restart")
                    font.bold: true
                    font.pixelSize: 20
                    color: settingsLevelMouseArea.pressed ? "steelblue" : "white"
                }
                MouseArea {
                    id: settingsLevelMouseArea
                    anchors.fill: parent
                    onClicked: {
                        root.visible = false
                        gameEngine.restartGame()
                    }
                }
            }

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - 20
                anchors {
                    left: parent.left
                    leftMargin: 10
                }
                color: "transparent"
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    // TRANSLATORS: The "Level selection" button in the pause menu
                    text: qsTr("Level selection")
                    font.bold: true
                    font.pixelSize: 20
                    color: selectLevelMouseArea.pressed ? "steelblue" : "white"
                }
                MouseArea {
                    id: selectLevelMouseArea
                    anchors.fill: parent
                    onClicked: {
                        gameEngine.stopGame()
                        root.visible = false
                        pageStack.pop()
                    }
                }
            }
        }

        Rectangle {
            id: closeButton
            width: buttonSize
            height: width
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: 1

            Image {
                id: closeIcon
                anchors.fill: parent
                anchors.margins: height / 4
                source: dataDirectory + "/images/close-white.png"
            }


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.visible = false
                    gameEngine.continueGame()
                }
            }
        }

        Rectangle {
            id: helpButton
            width: buttonSize
            height: width
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "?"
                color: "white"
                font.bold: true
                font.pixelSize: parent.height * 0.8
            }

            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.push(Qt.resolvedUrl("Help.qml"))
            }
        }

        Rectangle {
            id: muteButton
            width: buttonSize
            height: width
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: 1

            Image {
                id: muteImage
                anchors.fill: parent
                anchors.margins: height / 4
                source: gameEngine.playerSettings.muted ? dataDirectory + "/images/unmute.png" : dataDirectory + "/images/mute.png"
            }

            MouseArea {
                id: muteButtonMouseArea
                anchors.fill: parent
                onClicked: {
                    gameEngine.playerSettings.muted = !gameEngine.playerSettings.muted
                    app.updateMusic()
                }
            }
        }
    }
}
