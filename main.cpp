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
#include <QIcon>
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
    app.setApplicationVersion("0.5");
    app.setApplicationDisplayName("Monster Wars");
    app.setWindowIcon(QIcon("qrc:///images/icon.png"));

    // command line parser
    QCommandLineOption windowOption(QStringList() << "w" << "window-mode", QCoreApplication::translate("main", "Run Monster Wars in a window (default: \"fullscreen\")"));
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription(QString("\nStrategy game consisting of a pillow fight between monsters.\n\n"
                                             "Copyright %1 2015 Simon Stürz <stuerz.simon@gmail.com>\n"
                                             "Released under the GNU GPLv3.").arg(QChar(0xA9)));
    parser.addPositionalArgument("dataPath", "The relative file path where the \"levels\" and \"sounds\" folders can be found (optional).", "[dataPath]");
    parser.addOption(windowOption);
    parser.process(app);

    // register qml types
    qmlRegisterType<GameEngine>("MonsterWars", 1, 0, "GameEngine");
    qmlRegisterUncreatableType<Board>("MonsterWars", 1, 0, "Board", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Monster>("MonsterWars", 1, 0, "Monster", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<MonsterModel>("MonsterWars", 1, 0, "MonsterModel", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<Level>("MonsterWars", 1, 0, "Level", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<LevelModel>("MonsterWars", 1, 0, "LevelModel", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<AttackPillowModel>("MonsterWars", 1, 0, "AttackPillowModel", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Player>("MonsterWars", 1, 0, "Player", "Can't create this in QML. Get it from Board.");
    qmlRegisterUncreatableType<PlayerSettings>("MonsterWars", 1, 0, "PlayerSettings", "Can't create this in QML. Get it from GameEngine.");

    QQuickView view;
    view.setIcon(QIcon("qrc:///images/icon.png"));
    // check data file path
    if (!parser.positionalArguments().isEmpty()) {
        QDir dataDir(QDir::cleanPath(QCoreApplication::applicationDirPath() + "/" + parser.positionalArguments().first()));
        if (!dataDir.exists()) {
            qWarning() << dataDir.path() << "does not exist.";
            exit(-1);
        }
        view.engine()->rootContext()->setContextProperty("dataDirectory", "file://" + dataDir.path() + "/");
    } else {
        view.engine()->rootContext()->setContextProperty("dataDirectory", "file://" + QCoreApplication::applicationDirPath() + "/../../../data/");
    }

    view.engine()->rootContext()->setContextProperty("version", app.applicationVersion());
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

