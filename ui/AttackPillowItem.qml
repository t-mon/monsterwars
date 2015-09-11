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
    property real animationDuration: distance * 120 / (1 + speed * 0.25)

    Rectangle {
        id: pillowRectangle
        width: nodeDistance * 5
        height: width
        color: "transparent"

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:///monsters/pillow.png"
        }

        RotationAnimator {
            id: pillowRotationAnimation
            target: backgroundImage
            running: true
            from: 0;
            to: 360;
            duration: animationDuration
        }

        Text {
            id: valueLabel
            anchors.centerIn: parent
            text: value
            font.bold: true
            font.pixelSize: nodeDistance * 2
            style: Text.Outline
            styleColor: "steelblue"
            color: colorString
        }

        ParallelAnimation {
            id: attackAnimation
            running: true
            SequentialAnimation {
                id: flightAnimation
                loops: 1
                PropertyAnimation {
                    target: root
                    properties: "scale"
                    from: 0.9
                    to: 1.3
                    easing.type: Easing.OutQuad
                    duration: xAnimation.duration / 2
                }
                PropertyAnimation {
                    target: root
                    properties: "scale"
                    from: 1.3
                    to: 0.9
                    easing.type: Easing.InQuad
                    duration: xAnimation.duration / 2
                }
            }

            NumberAnimation {
                id: xAnimation
                target: root
                property: "x"
                from: root.nodeDistance * sourceX - pillowRectangle.width / 2
                to: root.nodeDistance * destinationX - pillowRectangle.width / 2
                duration: animationDuration
            }
            NumberAnimation {
                id: yAnimation
                target: root
                property: "y"
                from: root.nodeDistance * sourceY - pillowRectangle.height / 2
                to: root.nodeDistance * destinationY - pillowRectangle.width / 2
                duration: animationDuration
            }
            onStopped: {
                gameEngine.attackFinished(pillowId)
            }
        }

        Connections {
            target: gameEngine
            onRunningChanged: {
                if (!gameEngine.running) {
                    attackAnimation.pause()
                    pillowRotationAnimation.pause()
                } else {
                    attackAnimation.resume()
                    pillowRotationAnimation.resume()
                }
            }
        }
    }
}
