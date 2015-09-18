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
    visible: false
    property real buttonSize: units.gu(7)

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
        anchors.margins: units.gu(5)
        radius: units.gu(2)

        Column {
            id: pauseMenuColumn
            anchors.fill: parent

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - units.gu(20)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "transparent"
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: units.gu(2)
                        verticalCenter: parent.verticalCenter
                    }
                    // TRANSLATORS: The "Continue" button in the pause menu
                    text: i18n.tr("Continue")
                    font.bold: true
                    font.pixelSize: units.gu(4)
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
                width: menuRectangle.width - units.gu(20)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "transparent"
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: units.gu(2)
                        verticalCenter: parent.verticalCenter
                    }
                    // TRANSLATORS: The "Restart" button in the pause menu
                    text: i18n.tr("Restart")
                    font.bold: true
                    font.pixelSize: units.gu(4)
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
                width: menuRectangle.width - units.gu(20)
                anchors {
                    left: parent.left
                    leftMargin: units.gu(2)
                }
                color: "transparent"
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: units.gu(2)
                        verticalCenter: parent.verticalCenter
                    }
                    // TRANSLATORS: The "Level selection" button in the pause menu
                    text: i18n.tr("Level selection")
                    font.bold: true
                    font.pixelSize: units.gu(4)
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
            anchors.rightMargin: units.gu(1)
            anchors.top: parent.top
            anchors.topMargin: units.gu(1)
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: units.gu(0.25)

            Image {
                id: closeIcon
                anchors.fill: parent
                anchors.margins: units.gu(2)
                source: "qrc:///images/close-white.png"
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
            anchors.rightMargin: units.gu(1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: units.gu(0.25)

            Text {
                anchors.centerIn: parent
                text: "?"
                color: "white"
                font.bold: true
                font.pixelSize: units.gu(6)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.push(helpPage)
            }
        }

        Rectangle {
            id: muteButton
            width: buttonSize
            height: width
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)
            anchors.verticalCenter: parent.verticalCenter
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: units.gu(0.25)

            Image {
                id: muteImage
                anchors.fill: parent
                anchors.margins: units.gu(1)
                source: gameEngine.playerSettings.muted ? "qrc:///images/unmute.png" : "qrc:///images/mute.png"
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
