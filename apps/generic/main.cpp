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
#include <QCommandLineOption>
#include <QtQml>
#include <QtQml/QQmlContext>

#include "gameengine.h"
#include "player.h"
#include "monster.h"
#include "level.h"
#include "board.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("monsterwars");
    app.setApplicationVersion("1.0.0");
    app.setApplicationDisplayName("Monster Wars");
    app.setWindowIcon(QIcon("qrc:///images/icon.png"));

    // Command line parser
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription(QString("\nStrategy game consisting of a pillow fight between monsters.\n\n"
                                             "Copyright %1 2015 -2017 Simon Stürz <stuerz.simon@gmail.com>\n"
                                             "Released under the GNU GPLv3.").arg(QChar(0xA9)));

    // Options
    QCommandLineOption windowOption(QStringList() << "w" << "window-mode");
    windowOption.setDescription(QCoreApplication::translate("main", "Run Monster Wars in a window (default: \"fullscreen\")"));
    parser.addOption(windowOption);

    QCommandLineOption dataPathOption(QStringList() << "d" << "data");
    dataPathOption.setValueName("path");
    dataPathOption.setDescription("The relative file path where the \"levels\" and \"sounds\" folders can be found (optional).");
    dataPathOption.setDefaultValue("/usr/share/monsterwars");
    parser.addOption(dataPathOption);

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

    // check data file path
    QString dataPath = parser.value(dataPathOption);
    QDir dataDir(QDir::cleanPath(dataPath));
    if (!dataDir.exists()) {
        qWarning() << dataDir.path() << "does not exist.";
        exit(-1);
    }
    qDebug() << "Using data directory" << dataDir.canonicalPath();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataDirectory", "file:" + dataDir.canonicalPath());
    engine.rootContext()->setContextProperty("fullscreen", !parser.isSet(windowOption));
    engine.rootContext()->setContextProperty("version", app.applicationVersion());

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    // connect quit signal from QML engine (quit button pressed)
    //QObject::connect(engine, SIGNAL(quit()), qApp, SLOT(quit()));

    return app.exec();
}

