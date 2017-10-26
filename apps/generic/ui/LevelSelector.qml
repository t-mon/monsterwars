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

import MonsterWars 1.0

Page {
    id: levelSelectorPage

    Image {
        id: backgroundImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        sourceSize: Qt.size(parent.width, 0)
        source: Qt.resolvedUrl(dataDirectory + "/backgrounds/menu-background.jpg")
    }

    GridView {
        id: levelGrid
        cellWidth: parent.width / 2
        cellHeight: cellWidth * 0.62

        model: gameEngine.levels
        anchors {
            top: menuBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        delegate: LevelSelectorItem {
            width: levelGrid.cellWidth
            height: levelGrid.cellHeight
            name: model.levelName
            levelId: model.levelId
            bestTime: model.bestTime
            unlocked: model.unlocked
            onSelected: {
                pageStack.push(Qt.resolvedUrl("BoardView.qml"))
                gameEngine.startGame(model.levelId)
            }
        }
    }

    MenuBar {
        id: menuBar
        height: 20
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        // TRANSLATORS: The title of the "Level selection" view
        menuTitle: qsTr("Level selection")
    }
}


