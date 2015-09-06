import QtQuick 2.2
import Ubuntu.Components 1.1
import MonsterWars 1.0

MainView {
    id: app
    objectName: "mainView"
    automaticOrientation: true
    useDeprecatedToolbar: false

    width: units.gu(70)
    height: units.gu(40)


    GameEngine {
        id: gameEngine
        dataDir: "../../../levels"
        Component.onCompleted: pageStack.push(mainPage)
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(mainPage)

        Page {
            id: mainPage
            anchors.fill: parent
            visible: false

            Rectangle {
                anchors.fill: parent
                color: "black"

                Column {
                    id: mainMenu
                    anchors.fill: parent
                    anchors.topMargin: units.gu(3)
                    spacing: units.gu(5)

                    MainMenuItem {
                        name: "Play"
                        height: units.gu(10)
                        width: parent.width - units.gu(20)
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: pageStack.push(levelSelectorPage)
                    }

                    MainMenuItem {
                        name: "Settings"
                        height: units.gu(10)
                        width: parent.width - units.gu(20)
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: pageStack.push(settingsPage)
                    }
                }
            }
        }

        Page {
            id: levelSelectorPage
            visible: false
            LevelSelector {
                id: levelSelector
                anchors.fill: parent
            }
        }

        Page {
            id: boardPage
            visible: false
            BoardView {
                id: boardView
                anchors.fill: parent
            }
        }

        Page {
            id: settingsPage
            visible: false
            Settings {
                id: settings
                anchors.fill: parent
            }
        }
    }
}

