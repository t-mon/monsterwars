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
    property int levelId
    property bool unlocked
    property string bestTime
    property string name

    signal selected()

    Rectangle {
        id: levelItem
        anchors.fill: parent
        anchors.margins: units.gu(3)
        color: "black"
        radius: units.gu(2)
        border.color: levelMouseArea.pressed ? "steelblue" : "white"

        Text {
            anchors.centerIn: parent
            text: levelId
            font.bold: true
            font.pixelSize: units.gu(4)
            color: levelMouseArea.pressed ? "steelblue" : "white"
        }

        Text {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)
            anchors.horizontalCenter: parent.horizontalCenter
            text: bestTime
            font.bold: true
            font.pixelSize: units.gu(3)
            color: levelMouseArea.pressed ? "steelblue" : "white"
        }

        MouseArea {
            id: levelMouseArea
            anchors.fill: parent
            onClicked: root.selected()
        }
    }
}
