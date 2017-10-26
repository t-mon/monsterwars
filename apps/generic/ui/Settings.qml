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
import QtQuick.Controls 2.0

Page {
    id: root

    property string backgroundColor: "transparent"

    Rectangle {
        anchors.fill: parent
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            sourceSize: Qt.size(parent.width, 0)
            source: Qt.resolvedUrl(dataDirectory + "/backgrounds/menu-background.jpg")
        }

        Flickable {
            anchors.top: menuBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 2
            contentHeight: column.height


            Rectangle {
                id: restoreButton
                visible: gameEngine.playerSettings.changed
                anchors {
                    left: column.right
                    leftMargin: 2
                    top: column.top
                }
                width: 6
                height: width
                radius: width / 2
                color: "black"

                Image {
                    id: restartImage
                    anchors.fill: parent
                    anchors.margins: 1
                    source: dataDirectory + "/images/restart.png"
                }

                MouseArea {
                    id: restoreMouseArea
                    anchors.fill: parent
                    onClicked: gameEngine.playerSettings.restore()
                }
            }

            Column {
                id: column
                spacing: 1

                Text {
                    id: pointText
                    // TRANSLATORS: Describes the available points in the settings view for tuning your monster properties
                    text: qsTr("Available points") + ": " + gameEngine.playerSettings.tunePoints
                    font.weight: Font.DemiBold
                    style: Text.Outline
                    styleColor: "white"
                    font.pixelSize: 4
                }

                Row {
                    spacing: 0.5
                    Rectangle {
                        id: strengthPlusRectangle
                        height: 5
                        width: height
                        radius: 1
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: 1
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseStrengthPoints()
                        }
                    }

                    Rectangle {
                        id: strengthBackground
                        height: 5
                        width: 50
                        radius: 2
                        color: backgroundColor
                        border.color: "black"
                        border.width: 0.25

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
                            text: qsTr("Strength")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: 3
                        }
                    }
                }

                Row {
                    spacing: 0.5
                    Rectangle {
                        id: defensePlusRectangle
                        height: 5
                        width: height
                        radius: 1
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: 1
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseDefensePoints()
                        }
                    }

                    Rectangle {
                        id: defenseBackground
                        height: 5
                        width: 50
                        radius: 2
                        color: backgroundColor
                        border.color: "black"
                        border.width: 0.25

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
                            text: qsTr("Defense")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: 3
                        }
                    }
                }
                Row {
                    spacing: 0.5
                    Rectangle {
                        id: reproductionPlusRectangle
                        height: 5
                        width: height
                        radius: 1
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: 1
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseReproductionPoints()
                        }
                    }

                    Rectangle {
                        id: reproductionBackground
                        height: 5
                        width: 50
                        radius: 2
                        color: backgroundColor
                        border.color: "black"
                        border.width: 0.25

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
                            text: qsTr("Reproduction")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: 3
                        }
                    }
                }

                Row {
                    spacing: 0.5
                    Rectangle {
                        id: speedPlusRectangle
                        height: 5
                        width: height
                        radius: 1
                        color: "black"
                        border.color: "black"
                        border.width: 0.25

                        Image {
                            anchors.fill: parent
                            anchors.margins: 1
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseSpeedPoints()
                        }
                    }

                    Rectangle {
                        id: speedBackground
                        height: 5
                        width: 50
                        radius: 2
                        color: backgroundColor
                        border.color: "black"
                        border.width: 0.25

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
                            text: qsTr("Speed")
                            color: "white"
                            font.weight: Font.DemiBold
                            style: Text.Outline
                            styleColor: "black"
                            font.pixelSize: 3
                        }
                    }
                }


                Button {
                    id: resetButton
                    anchors.left: parent.left
                    // TRANSLATORS: Reset button to reset all game settings and achievements
                    text: qsTr("Reset")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ResetView.qml"))
                    }
                }
            }
        }

        MenuBar {
            id: menuBar
            height: 4
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            // TRANSLATORS: Title of the "Settings" view
            menuTitle: qsTr("Settings:")
            onCloseClicked: gameEngine.playerSettings.store()
        }
    }
}
