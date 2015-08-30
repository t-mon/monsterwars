import QtQuick 2.2
import QtQuick.Layouts 1.1

Item {
    id: root
    property string name
    signal clicked()

    Rectangle {
        id: menuButton
        anchors.fill: parent
        color: "black"
        border.color: buttonMouseArea.pressed ? "steelblue" : "white"
        border.width:  units.gu(1)
        radius: units.gu(5)

        Text {
            anchors.centerIn: menuButton
            text: name
            font.bold: true
            font.pixelSize: units.gu(6)
            color: buttonMouseArea.pressed ? "steelblue" : "white"
        }

        MouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: root.clicked()

        }
    }
}
