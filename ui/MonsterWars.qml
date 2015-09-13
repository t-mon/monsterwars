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
import Ubuntu.Components 1.1

MainView {
    id: app
    objectName: "mainView"
    applicationName: "monsterwars.simonstuerz"
    automaticOrientation: true
    useDeprecatedToolbar: false

    property string version: "0.1"

    width: units.gu(70)
    height: units.gu(40)


    GameEngine {
        id: gameEngine
        dataDir: "../../../levels"
        Component.onCompleted: {
            i18n.domain = "monsterwars.simonstuerz"
            pageStack.push(mainPage)
        }
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(mainPage)

        Page {
            id: mainPage
            anchors.fill: parent
            visible: false
            MainMenu {
                id: mainMenu
                anchors.fill: parent
            }
        }

        Page {
            id: levelSelectorPage
            visible: false
            LevelSelector {
                id: levelSelector
                anchors.fill: parent
            }
        }

        Page {
            id: boardPage
            visible: false
            BoardView {
                id: boardView
                anchors.fill: parent
            }
        }

        Page {
            id: settingsPage
            visible: false
            Settings {
                id: settings
                anchors.fill: parent
            }
        }

        Page {
            id: infoPage
            visible: false
            Info {
                id: info
                anchors.fill: parent
            }
        }

        Page {
            id: helpPage
            visible: false
            Help {
                id: help
                anchors.fill: parent
            }
        }
    }
}

