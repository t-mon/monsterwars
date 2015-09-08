import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0
import Ubuntu.Components 1.1

Rectangle {
    id: pauseMenu
    visible: false
    anchors.fill: parent
    color: "#99FFFFFF"

    MouseArea {
        anchors.fill: parent
        onClicked: {
            pauseMenu.visible = false
            gameEngine.continueGame()
        }
    }

    Rectangle {
        id: menuRectangle
        color: "black"
        anchors.fill: parent
        anchors.margins: units.gu(5)
        radius: units.gu(2)

        Rectangle {
            id: closeRectangle
            anchors.right: menuRectangle.right
            anchors.rightMargin: units.gu(2)
            anchors.top: menuRectangle.top
            anchors.topMargin: units.gu(2)
            width: units.gu(5)
            height: units.gu(5)
            color: closePauseRectangle.pressed ? "steelblue" : "white"
            radius: units.gu(1)

            MouseArea {
                id: closePauseRectangle
                anchors.fill: closeRectangle
                onClicked: {
                    pauseMenu.visible = false
                    gameEngine.continueGame()
                }
            }
        }

        Column {
            id: pauseMenuColumn
            anchors.fill: parent

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - units.gu(20)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "black"
                Text {
                    anchors.centerIn: parent
                    text: "Continue"
                    font.bold: true
                    font.pixelSize: units.gu(4)
                    color: continueMouseArea.pressed ? "steelblue" : "white"
                }
                MouseArea {
                    id: continueMouseArea
                    anchors.fill: parent
                    onClicked: {
                        pauseMenu.visible = false
                        gameEngine.continueGame()
                    }
                }
            }

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - units.gu(20)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "black"
                Text {
                    anchors.centerIn: parent
                    text: "Restart"
                    font.bold: true
                    font.pixelSize: units.gu(4)
                    color: settingsLevelMouseArea.pressed ? "steelblue" : "white"
                }
                MouseArea {
                    id: settingsLevelMouseArea
                    anchors.fill: parent
                    onClicked: {
                        pauseMenu.visible = false
                        gameEngine.restartGame()
                    }
                }
            }

            Rectangle {
                height: menuRectangle.height / 3
                width: menuRectangle.width - units.gu(20)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                color: "black"
                Text {
                    anchors.centerIn: parent
                    text: "Select Level"
                    font.bold: true
                    font.pixelSize: units.gu(4)
                    color: selectLevelMouseArea.pressed ? "steelblue" : "white"
                }
                MouseArea {
                    id: selectLevelMouseArea
                    anchors.fill: parent
                    onClicked: {
                        gameEngine.stopGame()
                        pauseMenu.visible = false
                        pageStack.pop()
                    }
                }
            }
        }
    }
}
