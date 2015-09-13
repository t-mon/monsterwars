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
        }
    }

    Rectangle {
        id: menuRectangle
        color: "black"
        anchors.fill: parent
        anchors.margins: units.gu(5)
        radius: units.gu(2)

        Column {
            anchors.centerIn: parent
            spacing: units.gu(4)

            Text {
                id: winnerText
                color: "white"
                text: gameEngine.winnerId == 1 ? "You won!" : "You lost."
                font.bold: true
                font.pixelSize: units.gu(4)
            }

            Text {
                id: timeText
                visible: gameEngine.winnerId == 1
                color: "white"
                text: gameEngine.gameTime
                font.bold: true
                font.pixelSize: units.gu(4)
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)

            id: retryButton
            color: "black"
            border.color: "steelblue"
            height: parent.height / 5
            width: parent.width / 3
            radius: units.gu(2)

            Text {
                anchors.centerIn: parent
                text: i18n.tr("Retry")
                color: "white"
                font.bold: true
                font.pixelSize: units.gu(4)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.visible = false
                    gameEngine.restartGame()
                }

            }
        }

        Rectangle {
            id: okButton
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)

            color: "black"
            border.color: "steelblue"
            height: parent.height / 5
            width: parent.width / 3
            radius: units.gu(2)

            Text {
                anchors.centerIn: parent
                text: i18n.tr("Ok")
                color: "white"
                font.bold: true
                font.pixelSize: units.gu(4)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.visible = false
                    gameEngine.stopGame()
                    pageStack.pop()
                }
            }
        }
    }
}

