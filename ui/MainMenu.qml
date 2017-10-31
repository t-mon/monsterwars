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

Page {
    id: mainPage

    Rectangle {
        anchors.fill: parent
        color: "black"
        focus: true

        Keys.onPressed: {
            console.log("back -> " + event.key);

            if (event.key == Qt.Key_Back) {
                event.accepted = true
                console.log("Back button captured")
            }
        }

        Image {
            id: backgroundImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            sourceSize: Qt.size(parent.width, 0)
            source: Qt.resolvedUrl(dataDirectory + "/backgrounds/menu-background.jpg")
        }


        BackgroundMonsters {
            anchors.fill: parent
        }

        Rectangle {
            id: playButton
            anchors.centerIn: parent
            height: app.unitSize * 15
            width: app.unitSize * 40
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            Image {
                id: playButtonMonster
                anchors.fill: parent
                source: dataDirectory + "/images/play-button.png"
            }

            Text {
                anchors.centerIn: parent
                // TRANSLATORS: The "Play" button in the main menu
                text: qsTr("Play")
                font.bold: true
                font.pixelSize: 30
                color: playButtonMouseArea.pressed ? "steelblue" : "white"
            }

            MouseArea {
                id: playButtonMouseArea
                anchors.fill: parent
                onClicked: pageStack.push(Qt.resolvedUrl("LevelSelector.qml"))
            }
        }

        SequentialAnimation {
            id: playButtonAnimation
            ScaleAnimator {
                target: playButton
                from: 0.99
                to: 1.03
                easing.type: Easing.Linear;
                duration: 1000
            }
            ScaleAnimator {
                target: playButton
                from: 1.03
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
        width: app.unitSize * 5
        height: width
        anchors.left: parent.left
        anchors.leftMargin: width / 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: width / 2
        color: "black"
        radius: width / 2

        Text {
            anchors.centerIn: parent
            // TRANSLATORS: The "i" in the information button in the main menu
            text: qsTr("i")
            color: "white"
            font.bold: true
            font.pixelSize: infoButton.width * 3 / 4
        }

        MouseArea {
            id: infoMouseArea
            anchors.fill: parent
            onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
        }
    }


    Rectangle {
        id: muteButton
        width: app.unitSize * 5
        height: width
        anchors.right: parent.right
        anchors.rightMargin: width / 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: width / 2
        color: "black"
        radius: width / 2

        Image {
            id: muteImage
            anchors.fill: parent
            anchors.margins: width / 5
            source: gameEngine.playerSettings.muted ? dataDirectory + "/images/unmute.png" : dataDirectory + "/images/mute.png"
        }

        MouseArea {
            id: muteButtonMouseArea
            anchors.fill: parent
            onClicked: {
                gameEngine.playerSettings.muted = !gameEngine.playerSettings.muted
                app.updateMusic()
            }
        }
    }

    Rectangle {
        id: settingsButton
        width: app.unitSize * 6
        height: width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: width / 2
        color: "black"
        radius: width / 2

        Image {
            id: settingsImage
            anchors.fill: parent
            anchors.margins: width / 7
            source: dataDirectory + "/images/settings.png"
        }

        MouseArea {
            id: settingsMouseArea
            anchors.fill: parent
            onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
        }
    }

    Rectangle {
        id: quitButton
        width: app.unitSize * 5
        height: width
        anchors.right: parent.right
        anchors.rightMargin: width / 2
        anchors.top: parent.top
        anchors.topMargin: width / 2
        color: "black"
        radius: width / 2

        Image {
            id: closeIcon
            anchors.fill: parent
            anchors.margins: quitButton.width / 4
            source: dataDirectory + "/images/close-white.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }
}
