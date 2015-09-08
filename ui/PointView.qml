import QtQuick 2.2
import QtQuick.Layouts 1.1
import MonsterWars 1.0

Item {
    id: root
    property var players

    Rectangle {
        id: background
        anchors.fill: parent
        color: "transparent"
    }

    Row {
        id: pointRow
        Repeater {
            model: players
            delegate: Rectangle {
                height: root.height
                anchors.topMargin: root.height / 10
                anchors.bottomMargin: root.height / 10
                width: root.width * model.percentage
                visible: model.pointCount == 0 ? false : true
                color: model.colorString
                Text {
                    anchors.centerIn: parent
                    text: model.pointCount + " | " + Math.round(model.percentage * 100) + "%"
                    font.bold: true
                    font.pixelSize: root.height / 2
                }

                Behavior on width {
                    NumberAnimation {
                        duration: 500
                        easing.type: Easing.OutQuad
                    }
                }
            }
        }
    }
}

