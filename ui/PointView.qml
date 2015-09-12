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
    property var players

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
    }

    Row {
        id: pointRow
        Repeater {
            model: players
            delegate: Rectangle {
                height: root.height
                anchors.topMargin: root.height / 10
                anchors.bottomMargin: root.height / 10
                width: root.width * model.percentage
                visible: model.pointCount == 0 ? false : true
                color: model.colorString
                Text {
                    anchors.centerIn: parent
                    text: model.pointCount + " | " + Math.round(model.percentage * 100) + "%"
                    font.bold: true
                    font.pixelSize: root.height / 2
                }

                Behavior on width {
                    NumberAnimation {
                        duration: 500
                        easing.type: Easing.OutQuad
                    }
                }
            }
        }
    }
}

