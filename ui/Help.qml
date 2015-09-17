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
import QtQuick.Layouts 1.1

Item {
    id: root

    Rectangle {
        id: screenRectangle
        anchors.fill: parent
        color: "transparent"

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:///backgrounds/menu-background.jpg"
        }

        Flickable {
            anchors.top: menuBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: units.gu(2)
            contentHeight: columnLayout.height

            ColumnLayout {
                id: columnLayout
                spacing: units.gu(4)

                Row {
                    spacing: units.gu(5)
                    Rectangle {
                        id: normalRectangle
                        color: "transparent"
                        width: units.gu(15)
                        height: width

                        SpriteSequence {
                            id: normalSprite
                            anchors.fill: parent
                            interpolate: false
                            goalSprite: "still"
                            Sprite{
                                name: "still"
                                source: "qrc:///monsters/monster-normal-white.png"
                                frameCount: 6
                                frameWidth: 200
                                frameHeight: 200
                                frameDuration: 110
                            }
                        }

                        SequentialAnimation {
                            ScaleAnimator {
                                target: normalSprite
                                from: 0.98
                                to: 1.03
                                easing.type: Easing.Linear;
                                duration: 500
                            }
                            ScaleAnimator {
                                target: normalSprite
                                from: 1.03
                                to: 0.98
                                easing.type: Easing.Linear;
                                duration: 800
                            }
                            running: true
                            loops: Animation.Infinite
                        }
                    }

                    Text {
                        anchors.verticalCenter: normalRectangle.verticalCenter
                        // TRANSLATORS: Description of the monster type "Normal" in the help view, which has no special power or properties
                        text: i18n.tr("Normal")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }
                }

                Row {
                    spacing: units.gu(5)
                    Rectangle {
                        id: defenseRectangle
                        color: "transparent"
                        width: units.gu(15)
                        height: width

                        SpriteSequence {
                            id: defenseSprite
                            anchors.fill: parent
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
                        }

                        SequentialAnimation {
                            ScaleAnimator {
                                target: defenseSprite
                                from: 0.98
                                to: 1.03
                                easing.type: Easing.Linear;
                                duration: 500
                            }
                            ScaleAnimator {
                                target: defenseSprite
                                from: 1.03
                                to: 0.98
                                easing.type: Easing.Linear;
                                duration: 800
                            }
                            running: true
                            loops: Animation.Infinite
                        }
                    }

                    Text {
                        anchors.verticalCenter: defenseRectangle.verticalCenter
                        // TRANSLATORS: Description of the monster type "Defense" in the help view, which has + 4 defense points
                        text: i18n.tr("Defense") + " + 4"
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }
                }

                Row {
                    spacing: units.gu(5)
                    Rectangle {
                        id: speedRectangle
                        color: "transparent"
                        width: units.gu(15)
                        height: width

                        SpriteSequence {
                            id: speedSprite
                            anchors.fill: parent
                            interpolate: false
                            goalSprite: "still"
                            Sprite{
                                name: "still"
                                source: "qrc:///monsters/monster-speed-white.png"
                                frameCount: 6
                                frameWidth: 200
                                frameHeight: 200
                                frameDuration: 110
                            }
                        }

                        SequentialAnimation {
                            ScaleAnimator {
                                target: speedSprite
                                from: 0.98
                                to: 1.03
                                easing.type: Easing.Linear;
                                duration: 500
                            }
                            ScaleAnimator {
                                target: speedSprite
                                from: 1.03
                                to: 0.98
                                easing.type: Easing.Linear;
                                duration: 800
                            }
                            running: true
                            loops: Animation.Infinite
                        }
                    }

                    Text {
                        anchors.verticalCenter: speedRectangle.verticalCenter
                        // TRANSLATORS: Description of the monster type "Speed" in the help view, which has + 4 speed points
                        text: i18n.tr("Speed") + " + 4"
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }
                }

                Row {
                    spacing: units.gu(5)
                    Rectangle {
                        id: strengthRectangle
                        color: "transparent"
                        width: units.gu(15)
                        height: width

                        SpriteSequence {
                            id: strengthSprite
                            anchors.fill: parent
                            interpolate: false
                            goalSprite: "still"
                            Sprite{
                                name: "still"
                                source: "qrc:///monsters/monster-strength-white.png"
                                frameCount: 6
                                frameWidth: 200
                                frameHeight: 200
                                frameDuration: 110
                            }
                        }

                        SequentialAnimation {
                            ScaleAnimator {
                                target: strengthSprite
                                from: 0.98
                                to: 1.03
                                easing.type: Easing.Linear;
                                duration: 500
                            }
                            ScaleAnimator {
                                target: strengthSprite
                                from: 1.03
                                to: 0.98
                                easing.type: Easing.Linear;
                                duration: 800
                            }
                            running: true
                            loops: Animation.Infinite
                        }
                    }

                    Text {
                        anchors.verticalCenter: strengthRectangle.verticalCenter
                        // TRANSLATORS: Description of the monster type "Strength" in the help view, which has + 4 strength points
                        text: i18n.tr("Strength") + " + 4"
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }
                }

                Row {
                    spacing: units.gu(5)
                    Rectangle {
                        id: reproductionRectangle
                        color: "transparent"
                        width: units.gu(15)
                        height: width

                        SpriteSequence {
                            id: reproductionSprite
                            anchors.fill: parent
                            interpolate: false
                            goalSprite: "still"
                            Sprite{
                                name: "still"
                                source: "qrc:///monsters/monster-reproduction-white.png"
                                frameCount: 6
                                frameWidth: 200
                                frameHeight: 200
                                frameDuration: 110
                            }
                        }

                        SequentialAnimation {
                            ScaleAnimator {
                                target: reproductionSprite
                                from: 0.98
                                to: 1.03
                                easing.type: Easing.Linear;
                                duration: 500
                            }
                            ScaleAnimator {
                                target: reproductionSprite
                                from: 1.03
                                to: 0.98
                                easing.type: Easing.Linear;
                                duration: 800
                            }
                            running: true
                            loops: Animation.Infinite
                        }
                    }

                    Text {
                        anchors.verticalCenter: reproductionRectangle.verticalCenter
                        // TRANSLATORS: Description of the monster type "Reproduction" in the help view, which has + 4 reproduction points
                        text: i18n.tr("Reproduction") + " + 4"
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }
                }

                Row {
                    spacing: units.gu(5)
                    Rectangle {
                        id: pillowRectangle
                        color: "transparent"
                        width: units.gu(15)
                        height: width

                        Image {
                            id: pillowImage
                            anchors.fill: parent
                            anchors.margins: units.gu(3)
                            source: "qrc:///monsters/pillow.png"
                        }


                        RotationAnimator {
                            target: pillowImage
                            running: true
                            from: 0
                            to: 360
                            duration: 6000
                            loops: Animation.Infinite
                        }

                        SequentialAnimation {
                            ScaleAnimator {
                                target: pillowImage
                                from: 0.98
                                to: 1.03
                                easing.type: Easing.Linear;
                                duration: 500
                            }
                            ScaleAnimator {
                                target: pillowImage
                                from: 1.03
                                to: 0.98
                                easing.type: Easing.Linear;
                                duration: 800
                            }
                            running: true
                            loops: Animation.Infinite
                        }

                    }

                    Text {
                        anchors.verticalCenter: pillowRectangle.verticalCenter
                        // TRANSLATORS: Description of the pillow image in the Help view
                        text: i18n.tr("Pillow")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }
                }
            }
        }

        MenuBar {
            id: menuBar
            height: units.gu(4)
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            // TRANSLATORS: Title of the "Help" view
            menuTitle: i18n.tr("Help")
        }
    }
}
