#include "level.h"
#include "player.h"
#include "monster.h"

Level::Level(QObject *parent):
    QObject(parent)
{
}

Level::~Level()
{
}

void Level::setName(const QString &name)
{
    m_name = name;
}

QString Level::name() const
{
    return m_name;
}

void Level::setLevelId(const int &levelId)
{
    m_levelId = levelId;
}

int Level::levelId() const
{
    return m_levelId;
}

void Level::addMonster(Monster *monster)
{
    m_monsteres.append(monster);
}

QList<Monster *> Level::monsteres() const
{
    return m_monsteres;
}

Monster *Level::monster(int id) const
{
    foreach (Monster *monster, m_monsteres) {
        if(monster->id() == id){
            return monster;
        }
    }
    return NULL;
}

void Level::addPlayer(Player *player)
{
    m_players.append(player);
}

QList<Player *> Level::players() const
{
    return m_players;
}

Player *Level::player(int id) const
{
    foreach (Player *player, m_players) {
        if(player->id() == id){
            return player;
        }
    }
    return NULL;
}
