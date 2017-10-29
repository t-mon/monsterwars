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
import QtQuick.Layouts 1.3

import MonsterWars 1.0

Page {
    id: root

    property string backgroundColor: "transparent"

    Component.onDestruction: {
        console.log("Settings about to be destroyed. Save.")
        gameEngine.playerSettings.store()
    }

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
            anchors.margins: app.unitSize * 5
            contentHeight: column.height

            Column {
                id: column
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: app.unitSize

                Item {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    height: app.unitSize * 5

                    Text {
                        id: pointText
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Describes the available points in the settings view for tuning your monster properties
                        text: qsTr("Available points") + ": " + gameEngine.playerSettings.tunePoints
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: app.unitSize * 3
                    }

                    Rectangle {
                        id: restoreButton
                        visible: gameEngine.playerSettings.changed
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        width: app.unitSize * 4
                        height: width
                        radius: width / 2
                        color: "black"

                        Image {
                            id: restartImage
                            anchors.fill: parent
                            anchors.margins: app.unitSize
                            source: dataDirectory + "/images/restart.png"
                        }

                        MouseArea {
                            id: restoreMouseArea
                            anchors.fill: parent
                            onClicked: gameEngine.playerSettings.restore()
                        }
                    }
                }

                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Rectangle {
                        id: strengthPlusRectangle
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.preferredWidth: app.unitSize * 5
                        radius: height / 4
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: app.unitSize
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseStrengthPoints()
                        }
                    }

                    Rectangle {
                        id: strengthBackground
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.fillWidth: true
                        radius: height / 4
                        color: backgroundColor
                        border.color: "black"
                        border.width: app.unitSize / 2

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
                            font.pixelSize: app.unitSize * 2
                        }
                    }
                }

                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Rectangle {
                        id: defensePlusRectangle
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.preferredWidth: app.unitSize * 5
                        radius: height / 4
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: app.unitSize
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseDefensePoints()
                        }
                    }

                    Rectangle {
                        id: defenseBackground
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.fillWidth: true
                        radius: height / 4
                        color: backgroundColor
                        border.color: "black"
                        border.width: app.unitSize / 2

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
                            font.pixelSize: app.unitSize * 2
                        }
                    }
                }

                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Rectangle {
                        id: reproductionPlusRectangle
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.preferredWidth: app.unitSize * 5
                        radius: height / 4
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: app.unitSize
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseReproductionPoints()
                        }
                    }

                    Rectangle {
                        id: reproductionBackground
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.fillWidth: true
                        radius: height / 4
                        color: backgroundColor
                        border.color: "black"
                        border.width: app.unitSize / 2

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
                            font.pixelSize: app.unitSize * 2
                        }
                    }
                }


                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Rectangle {
                        id: speedPlusRectangle
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.preferredWidth: app.unitSize * 5
                        radius: height / 4
                        color: "black"

                        Image {
                            anchors.fill: parent
                            anchors.margins: app.unitSize
                            source: dataDirectory + "/images/plus.png"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: gameEngine.playerSettings.increaseSpeedPoints()
                        }
                    }

                    Rectangle {
                        id: speedBackground
                        Layout.preferredHeight: app.unitSize * 5
                        Layout.fillWidth: true
                        radius: height / 4
                        color: backgroundColor
                        border.color: "black"
                        border.width: app.unitSize / 2

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
                            font.pixelSize: app.unitSize * 2
                        }
                    }
                }


                Rectangle {
                    id: resetButton
                    height: app.unitSize * 12
                    width: app.unitSize * 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "transparent"

                    Image {
                        id: resetButtonMonster
                        anchors.fill: parent
                        source: dataDirectory + "/images/reset-button.png"
                    }

                    Text {
                        anchors.centerIn: parent
                        // TRANSLATORS: The "Donate" button in the main menu
                        text: qsTr("Reset")
                        font.bold: true
                        font.pixelSize: app.unitSize * 3
                        color: resetButtonMouseArea.pressed ? "steelblue" : "white"
                    }

                    MouseArea {
                        id: resetButtonMouseArea
                        anchors.fill: parent
                        onClicked: pageStack.push(Qt.resolvedUrl("ResetView.qml"))
                    }

                    SequentialAnimation {
                        id: resetButtonAnimation
                        ScaleAnimator {
                            target: resetButton
                            from: 0.99
                            to: 1.03
                            easing.type: Easing.Linear;
                            duration: 1000
                        }
                        ScaleAnimator {
                            target: resetButton
                            from: 1.03
                            to: 0.99
                            easing.type: Easing.Linear;
                            duration: 800
                        }
                        running: true
                        loops: Animation.Infinite
                    }
                }
            }
        }

        MenuBar {
            id: menuBar
            height: app.unitSize * 5
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
