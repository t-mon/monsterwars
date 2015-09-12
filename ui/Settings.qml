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

    Rectangle {
        anchors.fill: parent
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:///backgrounds/background1.jpg"
        }

        Rectangle {
            id: titleBar
            color: "black"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: units.gu(8)

            Text {
                id: title
                anchors.left: titleBar.left
                anchors.leftMargin: units.gu(3)
                anchors.top: titleBar.top
                anchors.topMargin: units.gu(1)
                text: "Tune your monster:"
                color: "white"
                font.bold: true
                font.pixelSize: units.gu(5)
            }

            Rectangle {
                id: exitRectangle
                anchors.right: titleBar.right
                anchors.rightMargin: units.gu(2)
                anchors.top: titleBar.top
                anchors.topMargin: units.gu(2)
                width: units.gu(5)
                height: units.gu(5)
                color: "transparent"
                radius: units.gu(1)

                Image {
                    id: closeIcon
                    anchors.fill: parent
                    source: "qrc:///images/close-white.png"
                }

                MouseArea {
                    anchors.fill: exitRectangle
                    onClicked: pageStack.pop()
                }
            }
        }
    }
}
