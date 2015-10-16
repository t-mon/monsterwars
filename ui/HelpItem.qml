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
    property string description
    property string type

    Row {
        anchors.fill: parent
        spacing: units.gu(5)
        Rectangle {
            id: imageRectangle
            color: "transparent"
            width: units.gu(15)
            height: width

            SpriteSequence {
                id: sprite
                anchors.fill: parent
                interpolate: false
                goalSprite: "still"

                Sprite{
                    name: "still"
                    source: "qrc:///monsters/monster-" + type + "-white.svg"
                    frameCount: 6
                    frameWidth: 500
                    frameHeight: 500
                    frameDuration: 110
                }

                Sprite{
                    name: "blink"
                    source: "qrc:///monsters/monster-" + type + "-white-blink.svg"
                    frameCount: 6
                    frameWidth: 500
                    frameHeight: 500
                    frameDuration: 110
                    to: { "still": 1 }
                }

            }

            SequentialAnimation {
                ScaleAnimator {
                    target: sprite
                    from: 0.98
                    to: 1.03
                    easing.type: Easing.Linear;
                    duration: 500
                }
                ScaleAnimator {
                    target: sprite
                    from: 1.03
                    to: 0.98
                    easing.type: Easing.Linear;
                    duration: 800
                }
                running: true
                loops: Animation.Infinite
            }

            MouseArea {
                anchors.fill: parent
                onClicked: sprite.jumpTo("blink")
            }
        }

        Text {
            id: descriptionText
            text: description
            anchors.verticalCenter: imageRectangle.verticalCenter
            font.weight: Font.DemiBold
            style: Text.Outline
            styleColor: "white"
            font.pixelSize: units.gu(4)
        }
    }

}
