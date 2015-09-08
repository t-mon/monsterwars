import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0

Rectangle {
    id: pauseMenu
    visible: false
    anchors.fill: parent
    color: "#99FFFFFF"

    Rectangle {
        id: menuRectangle
        color: "black"
        anchors.fill: parent
        anchors.margins: units.gu(5)
        radius: units.gu(2)

        Text {
            anchors.centerIn: parent
            color: "white"
            text: gameEngine.gameTime
            font.bold: true
            font.pixelSize: units.gu(4)
        }

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
    }
}
