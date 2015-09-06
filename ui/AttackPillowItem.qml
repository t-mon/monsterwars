import QtQuick 2.2
import MonsterWars 1.0

Item {
    id: root
    property real nodeDistance
    property real speed
    property real value
    property string pillowId
    property string colorString
    property real sourceX
    property real sourceY
    property real destinationX
    property real destinationY

    property real distance: Math.sqrt(Math.pow(sourceX - destinationX, 2) + Math.pow(sourceY - destinationY, 2))

    Rectangle {
        id: pillowRectangle
        width: units.gu(5)
        height: units.gu(5)
        color: "white"
        radius:  width / 2

        Text {
            id: valueLabel
            anchors.centerIn: parent
            text: value
            font.bold: true
            font.pixelSize: nodeDistance * 2
            color: colorString
        }

        ParallelAnimation {
            id: attackAnimation
            running: true
            NumberAnimation {
                target: root
                property: "x"
                from: root.nodeDistance * sourceX - pillowRectangle.width / 2
                to: root.nodeDistance * destinationX - pillowRectangle.width / 2
                duration: (distance * 100000) / ((speed * 200) + 1000)
            }
            NumberAnimation {
                target: root
                property: "y"
                from: root.nodeDistance * sourceY - pillowRectangle.height / 2
                to: root.nodeDistance * destinationY - pillowRectangle.width / 2
                duration: (distance * 100000) / ((speed * 200) + 1000)
            }
            onStarted: {
                var duration = (distance * 100000) / ((speed * 200) + 1000)
                console.log("uuid = " + pillowId + " distance = " + distance, "speed = " + speed + " -> " + duration)
            }
            onStopped: {
                gameEngine.attackFinished(pillowId)
            }

        }
    }
}
