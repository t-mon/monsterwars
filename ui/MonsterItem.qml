import QtQuick 2.2
import MonsterWars 1.0

Item {
    id: root
    property QtObject monster
    property real nodeDistance
    property bool pressed
    width: monster.size * nodeDistance * 2
    height: width
    x: monster.position.x * nodeDistance - width / 2
    y: monster.position.y * nodeDistance - width / 2

    Rectangle {
        id: monsterArea
        anchors.fill: parent
        radius: width / 2
        color: "transparent"

        Rectangle {
            id: monsterItem
            anchors.fill: parent
            anchors.margins: nodeDistance / 2
            border.color: monster.selected ? "steelblue" : "transparent"
            border.width: nodeDistance / 3
            color: "transparent"
            radius: width / 2


            SequentialAnimation {
                ScaleAnimator {
                    target: image
                    from: 0.98
                    to: 1.02
                    easing.type: Easing.Linear;
                    duration: 500
                }
                ScaleAnimator {
                    target: image
                    from: 1.02
                    to: 0.98
                    easing.type: Easing.Linear;
                    duration: 800
                }
                running: true
                loops: Animation.Infinite
            }


            SpriteSequence {
                id: image
                anchors.fill: monsterItem
                anchors.centerIn: monsterItem
                interpolate: false
                goalSprite: "still"
                Sprite{
                    name: "still"
                    source: "qrc:///monsters/monster-still-" + monster.colorString + ".png"
                    frameCount: 6
                    frameWidth: 200
                    frameHeight: 200
                    frameDuration: 110
                }
            }


            Text {
                id: counterLabel
                anchors.centerIn: parent
                visible: monster.value == 0 ? false : true
                text: monster.value
                font.bold: true
                font.pixelSize: nodeDistance * 2
                color: monster.color
            }

            Rectangle {
                id: descriptionRectangle
                visible: false
                width: 8.5 * nodeDistance
                height: 3.5 * nodeDistance
                radius: nodeDistance
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.top
                anchors.bottomMargin: nodeDistance / 2
                color: "#804682b4"
                border.color: "Black"

                Text {
                    id: descriptionText
                    visible: parent.visible
                    anchors.centerIn: descriptionRectangle
                    text: "id = " + monster.id + "\n" + monster.monsterTypeString
                    style: Text.Outline;
                    styleColor: "Black"
                    font.pixelSize: nodeDistance * 1.3
                    color: "white"
                }
            }

            MouseArea {
                id: monsterMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.AllButtons
                hoverEnabled: true
                onEntered: {
                    descriptionRectangle.visible = !pressed
                }
                onExited: descriptionRectangle.visible = false
            }

        }
    }
}



