import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0
import Ubuntu.Components 1.1

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:///backgrounds/background1.jpg"
        }

        Rectangle {
            id: titleBar
            color: "black"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: units.gu(8)

            Text {
                id: title
                anchors.left: titleBar.left
                anchors.leftMargin: units.gu(3)
                anchors.top: titleBar.top
                anchors.topMargin: units.gu(1)
                text: "About:"
                color: "white"
                font.family: "Comic Sans MS"
                font.bold: true
                font.pixelSize: units.gu(5)
            }

            Rectangle {
                id: exitRectangle
                anchors.right: titleBar.right
                anchors.rightMargin: units.gu(2)
                anchors.top: titleBar.top
                anchors.topMargin: units.gu(2)
                width: units.gu(5)
                height: units.gu(5)
                color: "transparent"
                radius: units.gu(1)

                Image {
                    id: closeIcon
                    anchors.fill: parent
                    source: "qrc:///images/close-white.png"
                }

                MouseArea {
                    anchors.fill: exitRectangle
                    onClicked: pageStack.pop()
                }
            }
        }
    }
}
