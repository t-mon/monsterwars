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
import Ubuntu.Components 1.1

Item {
    id: root

    property string backgroundColor: "transparent"

    Rectangle {
        anchors.fill: parent
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            sourceSize.width: parent.width
            sourceSize.height: parent.height
            source: "qrc:///images/menu-background.jpg"
        }

        Flickable {
            anchors.top: menuBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: units.gu(2)
            contentHeight: column.height


            Rectangle {
                id: restoreButton
                visible: gameEngine.playerSettings.changed
                anchors {
                    left: column.right
                    leftMargin: units.gu(2)
                    top: column.top
                    topMargin: units.gu(5)
                }
                width: units.gu(6)
                height: width
                radius: width / 2
                color: "black"

                Image {
                    id: restartImage
                    anchors.fill: parent
                    anchors.margins: units.gu(1)
                    source: "qrc:///images/restart.png"
                }

                MouseArea {
                    id: restoreMouseArea
                    anchors.fill: parent
                    onClicked: gameEngine.playerSettings.restore()
                }
            }

            Column {
                id: column
                spacing: units.gu(1)

                Text {
                    id: pointText
                    // TRANSLATORS: Describes the available points in the settings view for tuning your monster properties
                    text: i18n.tr("Available points") + ": " + gameEngine.playerSettings.tunePoints
                    font.weight: Font.DemiBold
                    style: Text.Outline
                    styleColor: "white"
                    font.pixelSize: units.gu(4)
                }

                Row {
                    spacing: units.gu(0.5)
                    Rectangle {
                        id: strengthPlusRectangle
                        height: units.gu(5)
                        width: height
                        radius: units.gu(1)
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            source: "qrc:///images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseStrengthPoints()
                        }
                    }

                    Rectangle {
                        id: strengthBackground
                        height: units.gu(5)
                        width: units.gu(50)
                        radius: units.gu(2)
                        color: backgroundColor
                        border.color: "black"
                        border.width: units.gu(0.25)

                        Rectangle {
                            id: strengthBar
                            height: parent.height
                            anchors.left: parent.left
                            width: parent.width * gameEngine.playerSettings.strengthPoints / 8
                            radius: parent.radius
                            color: "black"

                            Behavior on width {
                                NumberAnimation {
                                    duration: 300
                                    easing.type: Easing.OutQuad
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: i18n.tr("Strength")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: units.gu(3)
                        }
                    }
                }

                Row {
                    spacing: units.gu(0.5)
                    Rectangle {
                        id: defensePlusRectangle
                        height: units.gu(5)
                        width: height
                        radius: units.gu(1)
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            source: "qrc:///images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseDefensePoints()
                        }
                    }

                    Rectangle {
                        id: defenseBackground
                        height: units.gu(5)
                        width: units.gu(50)
                        radius: units.gu(2)
                        color: backgroundColor
                        border.color: "black"
                        border.width: units.gu(0.25)

                        Rectangle {
                            id: defenseBar
                            height: parent.height
                            anchors.left: parent.left
                            width: parent.width * gameEngine.playerSettings.defensePoints / 8
                            radius: parent.radius
                            color: "black"

                            Behavior on width {
                                NumberAnimation {
                                    duration: 300
                                    easing.type: Easing.OutQuad
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: i18n.tr("Defense")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: units.gu(3)
                        }
                    }
                }
                Row {
                    spacing: units.gu(0.5)
                    Rectangle {
                        id: reproductionPlusRectangle
                        height: units.gu(5)
                        width: height
                        radius: units.gu(1)
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            source: "qrc:///images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseReproductionPoints()
                        }
                    }

                    Rectangle {
                        id: reproductionBackground
                        height: units.gu(5)
                        width: units.gu(50)
                        radius: units.gu(2)
                        color: backgroundColor
                        border.color: "black"
                        border.width: units.gu(0.25)

                        Rectangle {
                            id: reproductionBar
                            height: parent.height
                            anchors.left: parent.left
                            width: parent.width * gameEngine.playerSettings.reproductionPoints / 8
                            radius: parent.radius
                            color: "black"

                            Behavior on width {
                                NumberAnimation {
                                    duration: 300
                                    easing.type: Easing.OutQuad
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: i18n.tr("Reproduction")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: units.gu(3)
                        }
                    }
                }

                Row {
                    spacing: units.gu(0.5)
                    Rectangle {
                        id: speedPlusRectangle
                        height: units.gu(5)
                        width: height
                        radius: units.gu(1)
                        color: "black"
                        border.color: "black"
                        border.width: units.gu(0.25)

                        Image {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            source: "qrc:///images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseSpeedPoints()
                        }
                    }

                    Rectangle {
                        id: speedBackground
                        height: units.gu(5)
                        width: units.gu(50)
                        radius: units.gu(2)
                        color: backgroundColor
                        border.color: "black"
                        border.width: units.gu(0.25)

                        Rectangle {
                            id: speedBar
                            height: parent.height
                            anchors.left: parent.left
                            width: parent.width * gameEngine.playerSettings.speedPoints / 8
                            radius: parent.radius
                            color: "black"

                            Behavior on width {
                                NumberAnimation {
                                    duration: 300
                                    easing.type: Easing.OutQuad
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: i18n.tr("Speed")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: units.gu(3)
                        }
                    }
                }


                Button {
                    id: resetButton
                    anchors.left: parent.left
                    // TRANSLATORS: Reset button to reset all game settings and achievements
                    text: i18n.tr("Reset")
                    gradient: UbuntuColors.orangeGradient
                    onClicked: {
                        pageStack.push(resetPage)
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
            // TRANSLATORS: Title of the "Settings" view
            menuTitle: i18n.tr("Settings:")
            onCloseClicked: gameEngine.playerSettings.store()
        }
    }
}
