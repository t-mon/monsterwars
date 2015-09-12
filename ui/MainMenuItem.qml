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

Item {
    id: root
    property string name
    signal clicked()

    Rectangle {
        id: menuButton
        anchors.fill: parent
        color: "black"
        radius: height / 2

        Text {
            anchors.centerIn: menuButton
            text: name
            font.bold: true
            font.pixelSize: units.gu(4)
            color: buttonMouseArea.pressed ? "steelblue" : "white"
        }

        MouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: root.clicked()

        }
    }
}
