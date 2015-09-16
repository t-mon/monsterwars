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
    property real nodeDistance
    property real speed
    property real value
    property string pillowId
    property string colorString
    property real sourceX
    property real sourceY
    property real destinationX
    property real destinationY

    property real distance: Math.sqrt(Math.pow(sourceX - destinationX, 2) + Math.pow(sourceY - destinationY, 2))
    property real animationDuration: distance * 160 / (1 + speed * 0.25)

    Rectangle {
        id: pillowRectangle
        width: nodeDistance * 5
        height: width
        color: "transparent"

        Image {
            id: pillowImage
            anchors.fill: parent
            source: "qrc:///monsters/pillow.png"
        }

        RotationAnimator {
            id: pillowRotationAnimation
            target: pillowImage
            running: true
            from: 0
            to: 360
            duration: animationDuration
        }

        Text {
            id: valueLabel
            anchors.centerIn: parent
            text: value
            font.bold: true
            font.pixelSize: nodeDistance * 2
            style: Text.Outline
            styleColor: "steelblue"
            color: colorString
        }

        ParallelAnimation {
            id: attackAnimation
            running: true
            onStopped: gameEngine.attackFinished(pillowId)
            SequentialAnimation {
                id: flightAnimation
                loops: 1
                PropertyAnimation {
                    target: root
                    properties: "scale"
                    from: 0.9
                    to: 1.2
                    easing.type: Easing.OutQuad
                    duration: xAnimation.duration / 2
                }
                PropertyAnimation {
                    target: root
                    properties: "scale"
                    from: 1.2
                    to: 0.9
                    easing.type: Easing.InQuad
                    duration: xAnimation.duration / 2
                }
            }

            NumberAnimation {
                id: xAnimation
                target: root
                property: "x"
                from: root.nodeDistance * sourceX - pillowRectangle.width / 2
                to: root.nodeDistance * destinationX - pillowRectangle.width / 2
                duration: animationDuration
            }

            NumberAnimation {
                id: yAnimation
                target: root
                property: "y"
                from: root.nodeDistance * sourceY - pillowRectangle.height / 2
                to: root.nodeDistance * destinationY - pillowRectangle.width / 2
                duration: animationDuration
            }
        }
    }

    Connections {
        target: gameEngine
        onRunningChanged: {
            if (!gameEngine.running) {
                attackAnimation.pause()
                pillowRotationAnimation.pause()
            } else {
                attackAnimation.resume()
                pillowRotationAnimation.resume()
            }
        }
    }
}

