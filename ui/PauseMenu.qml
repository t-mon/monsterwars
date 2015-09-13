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

        Rectangle {
            id: closeRectangle
            anchors.right: menuRectangle.right
            anchors.rightMargin: units.gu(2)
            anchors.top: menuRectangle.top
            anchors.topMargin: units.gu(2)
            width: units.gu(5)
            height: units.gu(5)
            color: "transparent"
            radius: units.gu(1)

            Image {
                id: closeIcon
                anchors.fill: parent
                source: "qrc:///images/close-white.png"
            }

            MouseArea {
                id: closePauseRectangle
                anchors.fill: closeRectangle
                onClicked: {
                    root.visible = false
                    gameEngine.continueGame()
                }
            }
        }

        Column {
            id: pauseMenuColumn
            anchors.fill: parent

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - units.gu(20)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "black"
                Text {
                    anchors.centerIn: parent
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
                color: "black"
                Text {
                    anchors.centerIn: parent
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
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "black"
                Text {
                    anchors.centerIn: parent
                    text: i18n.tr("Select Level")
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
    }
}
