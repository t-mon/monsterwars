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
        id: menuRectangle
        color: "black"
        anchors.fill: parent

        Column {
            anchors.centerIn: parent
            spacing: units.gu(4)

            Text {
                id: winnerText
                color: "white"
                text: gameEngine.winnerId == 1 ? "You are the winner!" : "You lost the game. \nPlayer " + gameEngine.winnerId + " won the game."
                font.bold: true
                font.pixelSize: units.gu(4)
            }

            Text {
                id: timeText
                color: "white"
                text: gameEngine.gameTime
                font.bold: true
                font.pixelSize: units.gu(4)
            }
        }
        Rectangle {
            id: closeRectangle
            anchors.right: menuRectangle.right
            anchors.rightMargin: units.gu(2)
            anchors.top: menuRectangle.top
            anchors.topMargin: units.gu(2)
            width: units.gu(5)
            height: units.gu(5)
            radius: units.gu(1)

            MouseArea {
                id: closePauseRectangle
                anchors.fill: closeRectangle
                onClicked: {
                    gameEngine.stopGame()
                    pageStack.pop()
                    root.visible = false
                }
            }
        }
    }
}
