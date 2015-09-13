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
            anchors.fill: parent
            source: "qrc:///backgrounds/background1.jpg"
        }

        Rectangle {
            id: randomPillow
            color: "transparent"
            width: units.gu(4)
            height: width
            x: Math.floor(Math.random() * (1 + root.width))
            y: Math.floor(Math.random() * (1 + root.height))

            Image {
                id: randomPillowImage
                anchors.fill: parent
                source: "qrc:///monsters/pillow.png"
            }

            Behavior on x {
                NumberAnimation {
                    target: randomPillow
                    properties: "x"
                    duration:4000
                    easing.type: Easing.OutCubic
                }
            }
            Behavior on y {
                NumberAnimation {
                    target: randomPillow
                    properties: "y"
                    duration: 4000
                    easing.type: Easing.OutCubic
                }
            }
            Timer {
                interval: 4000
                running: true
                repeat: true
                onTriggered: {
                    randomPillow.x = Math.floor(Math.random() * (1 + root.width))
                    randomPillow.y = Math.floor(Math.random() * (1 + root.height))
                }
            }
        }

        RotationAnimation {
            target: randomPillowImage
            running: true
            from: 0
            to: 360
            duration: 2000
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
                opacity: 0.8
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
                    duration: 6000
                    easing.type: Easing.OutCubic
                }
            }
            Behavior on y {
                NumberAnimation {
                    target: randomMonster
                    properties: "y"
                    duration: 6000
                    easing.type: Easing.OutCubic
                }
            }
            Timer {
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


        Rectangle {
            id: playButton
            anchors.centerIn: parent
            height: units.gu(15)
            width: units.gu(40)
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"
            Image {
                id: playButtonMonster
                anchors.fill: parent
                source: "qrc:///images/play-button.png"
            }
            Text {
                anchors.centerIn: parent
                text: i18n.tr("Play")
                font.bold: true
                font.pixelSize: units.gu(4)
                color: playButtonMouseArea.pressed ? "steelblue" : "white"
            }

            MouseArea {
                id: playButtonMouseArea
                anchors.fill: parent
                onClicked: pageStack.push(levelSelectorPage)
            }
        }
        SequentialAnimation {
            ScaleAnimator {
                target: playButton
                from: 0.99
                to: 1.01
                easing.type: Easing.Linear;
                duration: 1000
            }
            ScaleAnimator {
                target: playButton
                from: 1.01
                to: 0.99
                easing.type: Easing.Linear;
                duration: 800
            }
            running: true
            loops: Animation.Infinite
        }
    }

    Rectangle {
        id: infoButton
        width: units.gu(8)
        height: width
        anchors.left: parent.left
        anchors.leftMargin: units.gu(3)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: units.gu(3)
        color: "black"
        radius: width / 2

        Text {
            anchors.centerIn: parent
            text: i18n.tr("i")
            color: "white"
            font.bold: true
            font.pixelSize: units.gu(6)
        }

        MouseArea {
            id: infoMouseArea
            anchors.fill: parent
            onClicked: pageStack.push(infoPage)
        }
    }

    Rectangle {
        id: helpButton
        width: units.gu(8)
        height: width
        anchors.right: parent.right
        anchors.rightMargin: units.gu(3)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: units.gu(3)
        color: "black"
        radius: width / 2

        Text {
            anchors.centerIn: parent
            text: "?"
            color: "white"
            font.bold: true
            font.pixelSize: units.gu(6)
        }

        MouseArea {
            id: helpMouseArea
            anchors.fill: parent
            onClicked: pageStack.push(helpPage)
        }
    }
}
