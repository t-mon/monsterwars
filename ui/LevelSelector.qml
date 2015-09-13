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

    Rectangle {
        anchors.fill: parent
        color: "black"
        Image {
            anchors.fill: parent
            source: "qrc:///backgrounds/background1.jpg"
        }

        GridView {
            id: levelGrid
            anchors.fill: parent
            anchors.margins: units.gu(3)
            cellWidth: units.gu(30)
            cellHeight: units.gu(25)
            model: gameEngine.levels

            delegate: LevelSelectorItem {
                width: levelGrid.cellWidth
                height: levelGrid.cellHeight
                name: model.levelName
                levelId: model.levelId
                bestTime: model.bestTime
                unlocked: model.unlocked
                onSelected: {
                    pageStack.push(boardPage)
                    gameEngine.startGame(model.levelId)
                }
            }
        }
    }

    Rectangle {
        id: exitRectangle
        anchors.right: parent.right
        anchors.rightMargin: units.gu(2)
        anchors.top: parent.top
        anchors.topMargin: units.gu(2)
        width: units.gu(5)
        height: units.gu(5)
        color: "transparent"
        radius: units.gu(1)

        Image {
            id: closeIcon
            anchors.fill: parent
            source: "qrc:///images/close-black.png"
        }

        MouseArea {
            anchors.fill: exitRectangle
            onClicked: pageStack.pop()
        }
    }

}

