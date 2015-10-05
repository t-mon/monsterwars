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

Item{
    id: root

    Rectangle {
        id: randomPillow
        color: "transparent"
        width: units.gu(4)
        height: width
        x: Math.floor(Math.random() * (1 + root.width))
        y: Math.floor(Math.random() * (1 + root.height))

        Image {
            id: randomPillowImage
            opacity: 0.7
            anchors.centerIn: parent
            sourceSize.width: parent.width
            sourceSize.height: parent.height
            source: "qrc:///monsters/pillow.png"
        }

        Behavior on x {
            NumberAnimation {
                target: randomPillow
                properties: "x"
                duration: pillowTimer.interval
                easing.type: Easing.OutCubic
            }
        }
        Behavior on y {
            NumberAnimation {
                target: randomPillow
                properties: "y"
                duration: pillowTimer.interval
                easing.type: Easing.OutCubic
            }
        }
        Timer {
            id: pillowTimer
            interval: 4000
            running: true
            repeat: true
            onTriggered: {
                randomPillow.x = Math.floor(Math.random() * (1 + root.width))
                randomPillow.y = Math.floor(Math.random() * (1 + root.height))
            }
        }
    }

    RotationAnimator {
        target: randomPillowImage
        running: true
        from: 0
        to: 360
        duration: pillowTimer.interval
        easing.type: Easing.OutCubic;
        loops: Animation.Infinite
    }

    Rectangle {
        id: randomMonster
        color: "transparent"
        width: units.gu(8)
        height: width
        x: Math.floor(Math.random() * (1 + root.width))
        y: Math.floor(Math.random() * (1 + root.height))

        SequentialAnimation {
            ScaleAnimator {
                target: image
                from: 0.98
                to: 1.02
                easing.type: Easing.Linear;
                duration: 500
            }
            ScaleAnimator {
                target: image
                from: 1.02
                to: 0.98
                easing.type: Easing.Linear;
                duration: 800
            }
            running: true
            loops: Animation.Infinite
        }

        SpriteSequence {
            id: image
            width: parent.width
            height: width
            opacity: 0.6
            anchors.centerIn: parent
            interpolate: false
            goalSprite: "still"
            Sprite{
                name: "still"
                source: "qrc:///monsters/monster-defense-white.png"
                frameCount: 6
                frameWidth: 200
                frameHeight: 200
                frameDuration: 110
            }
            Sprite{
                name: "blink"
                source: "qrc:///monsters/monster-blink-white.png"
                frameCount: 6
                frameWidth: 200
                frameHeight: 200
                frameDuration: 110
                to: {"still":1}
            }
        }

        Behavior on x {
            NumberAnimation {
                target: randomMonster
                properties: "x"
                duration: monsterTimer.interval
                easing.type: Easing.OutCubic
            }
        }

        Behavior on y {
            NumberAnimation {
                target: randomMonster
                properties: "y"
                duration: monsterTimer.interval
                easing.type: Easing.OutCubic
            }
        }

        Timer {
            id: monsterTimer
            interval: 6000
            running: true
            repeat: true
            onTriggered: {
                randomMonster.x = Math.floor(Math.random() * (1 + root.width))
                randomMonster.y = Math.floor(Math.random() * (1 + root.height))
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: image.jumpTo("blink")
        }
    }
}
