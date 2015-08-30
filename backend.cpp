#include <QtQml>
#include <QtQml/QQmlContext>

#include "backend.h"
#include "gameengine.h"
#include "player.h"
#include "monster.h"
#include "level.h"
#include "board.h"

void BackendPlugin::registerTypes(const char *uri)
{

}

void BackendPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}
