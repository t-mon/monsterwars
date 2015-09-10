import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0

Item {
    id: root
    visible: false

    Rectangle {
        id: menuRectangle
        color: "black"
        anchors.fill: parent

        Column {
            anchors.centerIn: parent
            spacing: units.gu(4)

            Text {
                id: winnerText
                color: "white"
                text: gameEngine.winnerId == 1 ? "You are the winner!" : "You lost the game. \nPlayer " + gameEngine.winnerId + " won the game."
                font.bold: true
                font.pixelSize: units.gu(4)
            }

            Text {
                id: timeText
                color: "white"
                text: gameEngine.gameTime
                font.bold: true
                font.pixelSize: units.gu(4)
            }
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
                    gameEngine.stopGame()
                    pageStack.pop()
                    root.visible = false
                }
            }
        }
    }
}
