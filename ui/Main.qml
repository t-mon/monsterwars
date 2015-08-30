import QtQuick 2.2
import Ubuntu.Components 1.1
import MonsterWars 1.0

MainView {
    id: app
    objectName: "mainView"
    applicationName: "monsterwars.t-mon"
    automaticOrientation: true
    useDeprecatedToolbar: false

    width: units.gu(100)
    height: units.gu(75)

    GameEngine {
        id: gameEngine
        dataDir: "../../../levels"
    }

    BoardView {
        id: boardView
        board: gameEngine.board
        anchors.fill: parent
    }


}

