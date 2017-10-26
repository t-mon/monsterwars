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
        anchors.margins: 2
        color: "black"
        radius: height / 8
        //border.color: levelMouseArea.pressed && unlocked ? "steelblue" : "gray"
        //border.width: 5

        Image {
            id: levelPreview
            anchors.fill: parent
            opacity: unlocked ? 0.8 : 0.3
            anchors.margins: 10
            sourceSize: Qt.size(parent.width, parent.height)
            source: Qt.resolvedUrl("file:" + dataDirectory + "/levels/level" + levelId + "/preview.png")
        }

        Text {
            id: levelTimeText
            visible: unlocked
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            text: bestTime
            font.bold: true
            style: Text.Outline
            styleColor: "black"
            font.pixelSize: 10
            color: levelMouseArea.pressed && unlocked ? "steelblue" : "white"
        }

        Image {
            visible: !unlocked
            anchors.centerIn: parent
            height: parent.height * 2 / 3
            width: height
            source: "file:" + dataDirectory + "/images/lock.png"
        }

        Text {
            id: levelIdText
            anchors.centerIn: parent
            text: levelId
            font.bold: true
            font.pixelSize: 20
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
