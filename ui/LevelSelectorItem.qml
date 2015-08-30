import QtQuick 2.2
import QtQuick.Layouts 1.1

Item {
    id: root
    property int levelId
    property string name
    signal selected()

    Rectangle {
        id: menuButton
        anchors.fill: parent
        color: "black"
        border.color: buttonMouseArea.pressed ? "steelblue" : "white"
        border.width:  units.gu(0.5)
        radius: units.gu(1)

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: units.gu(3)
            text: name
            font.bold: true
            font.pixelSize: units.gu(4)
            color: buttonMouseArea.pressed ? "steelblue" : "white"
        }

        MouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: root.selected()
        }
    }
}
