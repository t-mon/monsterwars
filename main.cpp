/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Monster Wars.                                     *
 *                                                                         *
 *  Monster Wars is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Monster Wars is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Monster Wars. If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QCommandLineParser>
#include <QtQml>
#include <QtQml/QQmlContext>

#include "gameengine.h"
#include "player.h"
#include "monster.h"
#include "level.h"
#include "board.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationVersion("0.3");

    qmlRegisterType<GameEngine>("MonsterWars", 1, 0, "GameEngine");
    qmlRegisterUncreatableType<Board>("MonsterWars", 1, 0, "Board", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Monster>("MonsterWars", 1, 0, "Monster", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<MonsterModel>("MonsterWars", 1, 0, "MonsterModel", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<Level>("MonsterWars", 1, 0, "Level", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<LevelModel>("MonsterWars", 1, 0, "LevelModel", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<AttackPillowModel>("MonsterWars", 1, 0, "AttackPillowModel", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Player>("MonsterWars", 1, 0, "Player", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<PlayerSettings>("MonsterWars", 1, 0, "PlayerSettings", "Can't create this in QML. Get it from GameEngine.");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.setApplicationDescription("Strategy game consisting of a pillow fight between monsters.");
    QCommandLineOption developerOption(QStringList() << "d" << "developer", QCoreApplication::translate("main", "Run Monster Wars in developer mode"));
    QCommandLineOption windowOption(QStringList() << "w" << "window-mode", QCoreApplication::translate("main", "Run Monster Wars in a window"));
    parser.addOption(developerOption);
    parser.addOption(windowOption);
    parser.process(app);

    QQuickView view;
    if (parser.isSet(developerOption)) {
        view.engine()->rootContext()->setContextProperty("dataDirectory", "file://" + QCoreApplication::applicationDirPath() + "/data/");
    } else {
        view.engine()->rootContext()->setContextProperty("dataDirectory", "file://" + QCoreApplication::applicationDirPath() + "/../../../data/");
    }
    view.setSource(QUrl(QStringLiteral("qrc:///ui/MonsterWars.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    if (parser.isSet(windowOption)) {
        view.show();
    } else {
        view.showFullScreen();
    }

    // connect quit signal from QML engine (quit button pressed)
    QObject::connect(view.engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    return app.exec();
}

