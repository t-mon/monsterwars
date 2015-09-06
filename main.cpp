#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>
#include <QtQml/QQmlContext>

#include "gameengine.h"
#include "player.h"
#include "monster.h"
#include "node.h"
#include "level.h"
#include "board.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameEngine>("MonsterWars", 1, 0, "GameEngine");
    qmlRegisterUncreatableType<Board>("MonsterWars", 1, 0, "Board", "Can't create this in QML. Get it from Engine.");
    qmlRegisterUncreatableType<Monster>("MonsterWars", 1, 0, "Monster", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<Level>("MonsterWars", 1, 0, "Level", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<AttackPillow>("MonsterWars", 1, 0, "AttackPillow", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<Player>("MonsterWars", 1, 0, "Player", "Can't create this in QML. Get it from Board.");

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///ui/MonsterWars.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    return app.exec();
}

