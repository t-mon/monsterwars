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
            MainMenu {
                id: mainMenu
                anchors.fill: parent
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

        Page {
            id: infoPage
            visible: false
            Info {
                id: info
                anchors.fill: parent
            }
        }
    }
}

