import QtQuick 2.2
import MonsterWars 1.0

Item {
    id: root
    property real nodeDistance
    property int monsterValue
    property int monsterId
    property string monsterType
    property string monsterColor
    property int monsterSize
    property int positionX
    property int positionY
    property bool selected
    property bool pressed
    property real lineWidth

    width: monsterSize * nodeDistance * 2
    height: width
    x: positionX * nodeDistance - width / 2
    y: positionY * nodeDistance - width / 2

    Rectangle {
        id: monsterArea
        anchors.fill: parent
        radius: width / 2
        color: "transparent"

        Rectangle {
            id: monsterItem
            anchors.fill: parent
            color: "transparent"
            radius: width / 2

            SequentialAnimation {
                ScaleAnimator {
                    target: image
                    from: 0.98
                    to: 1.03
                    easing.type: Easing.Linear;
                    duration: 500
                }
                ScaleAnimator {
                    target: image
                    from: 1.03
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
                interpolate: true
                goalSprite: "still"
                Sprite{
                    name: "still"
                    source: "qrc:///monsters/monster-still-"+ monsterColor +".png"
                    frameCount: 6
                    frameWidth: 200
                    frameHeight: 200
                    frameDuration: 110
                }
            }

            Text {
                id: counterLabel
                anchors.centerIn: parent
                visible: monsterValue == 0 ? false : true
                text: monsterValue
                font.weight: Font.DemiBold
                style: Text.Outline
                styleColor: "gray"
                font.pixelSize: nodeDistance * 2
                color: monsterColor
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
                    text: "id = " + monsterId + "\n" + monsterType
                    style: Text.Outline
                    styleColor: "white"
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
        Rectangle {
            id: monsterSelectionCircle
            anchors.fill: parent
            border.color: selected ? "steelblue" : "transparent"
            border.width: lineWidth
            color: "transparent"
            radius: width / 2
        }
    }
}



