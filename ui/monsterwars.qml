import QtQuick 2.0
import Ubuntu.Components 1.1
import Viruswars 1.0
import "ui"
import Bacon2D 1.0

MainView {
    id: app
    width: units.gu(210)
    height: units.gu(137)
    applicationName: "viruswars"
    automaticOrientation: true
    property bool performanceOverlayEnabled: true
    useDeprecatedToolbar: false

    // Sizes
    property int appWidth: Math.max(app.height, app.width)


    GameEngine {
        id: gameEngine
        dataDir: Qt.resolvedUrl("../data/levels")
    }

    PointView {
        id: pointView
        players: gameEngine.board.players
        width: app.width
        height: width / 25
        anchors.top: parent.top
    }

    BoardView {
        id: boardView
        board: gameEngine.board
        anchors.top: pointView.bottom
        width: app.width
        height: width * board.rows / board.columns
    }
}



