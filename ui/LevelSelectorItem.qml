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

import QtQuick 2.4
import Ubuntu.Thumbnailer 0.1

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
        anchors.margins: units.gu(2)
        color: "black"
        radius: units.gu(1.5)
        border.color: levelMouseArea.pressed && unlocked ? "steelblue" : "gray"
        border.width: units.gu(0.3)

        Image {
            id: levelPreview
            anchors.fill: parent
            opacity: unlocked ? 0.8 : 0.3
            anchors.margins: units.gu(1.5)
            sourceSize: Qt.size(parent.width, parent.height)
            source: "image://thumbnailer/" + Qt.resolvedUrl(dataDirectory + "/levels/level" + levelId + "/preview.png")
        }

        Text {
            id: levelTimeText
            visible: unlocked
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(4)
            anchors.horizontalCenter: parent.horizontalCenter
            text: bestTime
            font.bold: true
            style: Text.Outline
            styleColor: "black"
            font.pixelSize: units.gu(2)
            color: levelMouseArea.pressed && unlocked ? "steelblue" : "white"
        }

        Image {
            visible: !unlocked
            anchors.centerIn: parent
            height: parent.height * 2 / 3
            width: height
            source: "qrc:///images/lock.png"
        }

        Text {
            id: levelIdText
            anchors.centerIn: parent
            text: levelId
            font.bold: true
            font.pixelSize: units.gu(5)
            style: Text.Outline
            styleColor: "steelblue"
            color: levelMouseArea.pressed && unlocked ? "steelblue" : "white"
        }

        MouseArea {
            id: levelMouseArea
            anchors.fill: parent
            onClicked: {
                if (unlocked) {
                    root.selected()
                }
            }
        }
    }
}
