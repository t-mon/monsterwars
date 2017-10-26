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
import QtQuick.Controls 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Page {
    id: root
    head {
        visible: false
        locked: true
    }

    Image {
        id: backgroundImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        sourceSize: Qt.size(parent.width, 0)
        source: Qt.resolvedUrl("file:" + dataDirectory + "/backgrounds/menu-background.jpg")
    }


    MenuBar {
        id: menuBar
        height: 4
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        menuTitle: qsTr("Tutorial")
    }
}
