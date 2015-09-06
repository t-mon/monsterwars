import QtQuick 2.2
import MonsterWars 1.0

Item {
    id: root
    property QtObject pillow
    property real nodeDistance

    property real dx: pillow.sourceMonster.position.x - pillow.destinationMonster.position.x
    property real dy: pillow.sourceMonster.position.y - pillow.destinationMonster.position.y
    property real distance: Math.sqrt(Math.pow(dx, 2) + Math.pow(dy, 2))

    Rectangle {
        id: pillowRectangle
        width: units.gu(5)
        height: units.gu(5)
        color: "white"
        radius:  width / 2

        Text {
            id: valueLabel
            anchors.centerIn: parent
            text: pillow.count
            font.bold: true
            font.pixelSize: nodeDistance * 2
            color: pillow.colorString
        }

        ParallelAnimation {
            id: attackAnimation
            running: true
            NumberAnimation {
                target: root
                property: "x"
                from: root.nodeDistance * pillow.sourceMonster.position.x - pillowRectangle.width / 2
                to: root.nodeDistance * pillow.destinationMonster.position.x - pillowRectangle.width / 2
                duration: (distance * 100000) / ((pillow.speed * 200) + 1000)
            }
            NumberAnimation {
                target: root
                property: "y"
                from: root.nodeDistance * pillow.sourceMonster.position.y - pillowRectangle.height / 2
                to: root.nodeDistance * pillow.destinationMonster.position.y - pillowRectangle.width / 2
                duration: (distance * 100000) / ((pillow.speed * 200) + 1000)
            }
            onStarted: {
                var duration = (distance * 100000) / ((pillow.speed * 200) + 1000)
                console.log("distance = " + distance, "speed = " + pillow.speed + " -> " + duration)
            }
            onStopped: {
                gameEngine.attackFinished(model.id)
            }

        }
    }
}
