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
    visible: false
    property real buttonSize: units.gu(7)

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        opacity: 0.4
        color: "black"

        MouseArea {
            anchors.fill: parent
        }
    }

    Rectangle {
        id: menuRectangle
        color: "black"
        anchors.fill: parent
        anchors.margins: units.gu(5)
        radius: units.gu(2)

        Text {
            id: newHighscoreText
            color: "white"
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: units.gu(1)
            }
            visible: gameEngine.newHighScore
            // TRANSLATORS: In the game over view, if you reached a new high score
            text: i18n.tr("New highscore!")
            style: Text.Outline
            styleColor: "steelblue"
            font.weight: Font.DemiBold
            font.bold: true
            font.pixelSize: units.gu(5)
        }

        SequentialAnimation {
            loops: Animation.Infinite
            running: gameEngine.newHighScore

            PropertyAnimation {
                target: newHighscoreText
                properties: "scale"
                from: 0.95
                to: 1
                easing.type: Easing.OutQuad
                duration: 1100
            }
            PropertyAnimation {
                target: newHighscoreText
                properties: "scale"
                from: 1
                to: 0.95
                easing.type: Easing.InQuad
                duration: 1000
            }
        }


        Column {
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: newHighscoreText.bottom
                topMargin: units.gu(1)
            }
            spacing: units.gu(1)

            Text {
                id: winnerText
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                // TRANSLATORS: Inform the player if he won or lost the game in the game over view
                text: gameEngine.winnerId == 1 ? i18n.tr("You won!") : i18n.tr("You lost.")
                font.bold: true
                font.pixelSize: units.gu(4)
            }

            Text {
                id: timeText
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                visible: gameEngine.winnerId == 1
                text: gameEngine.gameTime
                font.bold: true
                font.pixelSize: units.gu(4)
            }
        }

        Rectangle {
            id: retryButton
            width: buttonSize
            height: buttonSize
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: units.gu(0.25)

            Image {
                id: restartImage
                anchors.fill: parent
                anchors.margins: units.gu(1)
                source: "qrc:///images/restart.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.visible = false
                    gameEngine.restartGame()
                }
            }
        }

        Rectangle {
            id: settingsButton
            width: buttonSize
            height: buttonSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: units.gu(0.25)

            Image {
                id: settingsImage
                anchors.fill: parent
                anchors.margins: units.gu(1)
                source: "qrc:///images/settings.png"
            }

            MouseArea {
                id: settingsMouseArea
                anchors.fill: parent
                onClicked: pageStack.push(settingsPage)
            }
        }

        SequentialAnimation {
            loops: Animation.Infinite
            running: gameEngine.tunePointEarned && gameEngine.playerSettings.tunePoints != 0
            PropertyAnimation {
                target: settingsButton
                properties: "scale"
                from: 0.9
                to: 1
                easing.type: Easing.OutQuad
                duration: 700
            }
            PropertyAnimation {
                target: settingsButton
                properties: "scale"
                from: 1
                to: 0.9
                easing.type: Easing.InQuad
                duration: 1100
            }
        }


        Text {
            id: plusOneText
            anchors.verticalCenter: settingsButton.verticalCenter
            anchors.left: settingsButton.right
            anchors.leftMargin: units.gu(2)
            color: "white"
            text: "+1"
            style: Text.Outline
            styleColor: "steelblue"
            font.bold: true
            font.pixelSize: units.gu(4)
            visible: gameEngine.tunePointEarned && gameEngine.playerSettings.tunePoints != 0
        }

        SequentialAnimation {
            loops: Animation.Infinite
            running: gameEngine.tunePointEarned && gameEngine.playerSettings.tunePoints != 0
            PropertyAnimation {
                target: plusOneText
                properties: "scale"
                from: 0.8
                to: 1.1
                easing.type: Easing.OutQuad
                duration: 700
            }
            PropertyAnimation {
                target: plusOneText
                properties: "scale"
                from: 1.1
                to: 0.8
                easing.type: Easing.InQuad
                duration: 1100
            }
        }


        Rectangle {
            id: okButton
            width: buttonSize
            height: buttonSize
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: units.gu(1)
            color: "black"
            radius: width / 2
            border.color: "white"
            border.width: units.gu(0.25)

            Image {
                id: okImage
                anchors.fill: parent
                anchors.margins: units.gu(1)
                source: "qrc:///images/ok.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.visible = false
                    gameEngine.stopGame()
                    pageStack.pop()
                }
            }
        }
    }
}

