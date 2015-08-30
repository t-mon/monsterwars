import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0
import Ubuntu.Components 1.1

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "black"

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
                text: "Settings:"
                color: "white"
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
                color: "white"
                radius: units.gu(1)

                MouseArea {
                    anchors.fill: exitRectangle
                    onClicked: pageStack.pop()
                }
            }
        }
    }
}
