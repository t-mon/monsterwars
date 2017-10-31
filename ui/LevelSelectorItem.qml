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
import QtGraphicalEffects 1.0

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
        anchors.margins: app.unitSize * 2
        color: "black"
        radius: height / 8

        Image {
            id: img
            anchors.fill: parent
            anchors.margins: app.unitSize
            property bool rounded: true
            property bool adapt: true
            opacity: unlocked ? 0.8 : 0.3
            source: Qt.resolvedUrl(dataDirectory + "/levels/level" + levelId + "/preview.png")
            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: img.width
                    height: img.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: img.adapt ? img.width : Math.min(img.width, img.height)
                        height: img.adapt ? img.height : width
                        radius: height / 8
                    }
                }
            }
        }



        Text {
            id: levelTimeText
            visible: unlocked
            anchors.bottom: parent.bottom
            anchors.bottomMargin: app.unitSize
            anchors.horizontalCenter: parent.horizontalCenter
            text: bestTime
            font.bold: true
            style: Text.Outline
            styleColor: "black"
            font.pixelSize: app.unitSize * 2
            color: levelMouseArea.pressed && unlocked ? "steelblue" : "white"
        }

        Image {
            visible: !unlocked
            anchors.centerIn: parent
            height: parent.height * 2 / 3
            width: height
            source: dataDirectory + "/images/lock.png"
        }

        Text {
            id: levelIdText
            anchors.centerIn: parent
            text: levelId
            font.bold: true
            font.pixelSize: app.unitSize * 4
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
