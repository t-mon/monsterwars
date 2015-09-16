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

#include "board.h"
#include "level.h"
#include "gameengine.h"
#include "monster.h"
#include "player.h"
#include "attack.h"
#include "math.h"


#include <QJsonDocument>
#include <QSettings>

Board::Board(GameEngine *engine):
    QObject(engine),
    m_level(0),
    m_engine(engine),
    m_levelId(1)
{
    m_monsters = new MonsterModel(this);

    m_attack = new Attack(this);
    connect(m_attack, &Attack::attackFinished, this, &Board::attackFinished);
}

void Board::setLevel(Level *level)
{
    resetBoard();

    m_level = level;
    m_levelId = level->levelId();
    emit levelIdChanged();

    qDebug() << "loaded " << m_level->name() << "on board...";

    // add player 1 (the human player)
    Player *player = new Player(1, this);
    player->setColorString("blue");
    player->setPlayerType(Player::PlayerTypeHuman);
    player->setReproduction(m_engine->playerSettings()->reproductionPoints());
    player->setDefence(m_engine->playerSettings()->defensePoints());
    player->setStrength(m_engine->playerSettings()->strengthPoints());
    player->setSpeed(m_engine->playerSettings()->speedPoints());
    m_players.append(player);
    qDebug() << "    -> Create Player" << player->id() << player->playerTypeString();

    // add the dummy player from type PlayerTypeNone (id 0)
    Player *dummyPlayer = new Player(0, this);
    m_players.append(dummyPlayer);

    foreach (const QVariant &playerJson, m_level->playersVariant()) {
        m_players.append(createPlayer(playerJson.toMap()));
    }
    emit playersChanged();

    foreach (const QVariant &monsterJson, m_level->monstersVariant()) {
        m_monsters->addMonster(createMonster(monsterJson.toMap()));
    }
    emit monstersChanged();

    resetSelections();
}

Level *Board::level() const
{
    return m_level;
}

int Board::levelId() const
{
    return m_levelId;
}

QList<Player *> Board::playersList()
{
    return m_players;
}

QList<Monster *> Board::monstersList()
{
    return m_monsters->monsters();
}

QList<Monster *> Board::freeMonsters()
{
    QList<Monster *> freeMonsters;
    foreach (Monster *monster, m_monsters->monsters()) {
        if (monster->player()->id() == 0) {
            freeMonsters.append(monster);
        }
    }
    return freeMonsters;
}

QList<Monster *> Board::myMonsters(Player *player)
{
    QList<Monster *> myMonsters;
    foreach (Monster *monster, m_monsters->monsters()) {
        if (monster->player()->id() == player->id()) {
            myMonsters.append(monster);
        }
    }
    return myMonsters;
}

QList<Monster *> Board::enemyMonsters(Player *player)
{
    QList<Monster *> enemyMonsters;
    foreach (Monster *monster, m_monsters->monsters()) {
        if (monster->player()->id() != player->id() && monster->player()->id() !=0 ) {
            enemyMonsters.append(monster);
        }
    }
    return enemyMonsters;
}

QQmlListProperty<Player> Board::players()
{
    return QQmlListProperty<Player>(this, m_players);
}

MonsterModel *Board::monsters()
{
    return m_monsters;
}

int Board::rows() const
{
    return m_engine->rows();
}

int Board::columns() const
{
    return m_engine->columns();
}

int Board::monsterCount() const
{
    return m_monsters->monsters().count();
}

Monster *Board::monster(int id) const
{
    return m_monsters->monsterWithId(id);
}

Player *Board::player(int id) const
{
    foreach (Player *player, m_players) {
        if(player->id() == id){
            return player;
        }
    }
    return NULL;
}

void Board::evaluateReleased(const int &monsterId)
{
    Monster* m = monster(monsterId);
    m->select(true);
    if (m_attack->sourceIds().isEmpty()) {
        m_attack->beginnAttack(m->id());
    } else {
        // check if the source monsters are still my monster
        foreach (int sourceId, m_attack->sourceIds()) {
            Monster* sourceMonster = monster(sourceId);
            if (sourceMonster->player()->id() != 1) {
                qDebug() << "remove" << sourceId << "from attack, no longer my monster";
                m_attack->removeSourceId(sourceId);
            }
        }
        m_attack->endAttack(m->id());
    }
}

void Board::evaluateHovered(const bool &hovering, const int &monsterId)
{
    if (!m_engine->running())
        return;

    Monster* m = monster(monsterId);
    if (!hovering) {
        if (m->player()->id() != 1) {
            m->select(false);
        }
    }
    if (hovering) {
        if (m_attack->sourceIds().isEmpty() && m->player()->id() != 1) {
            return;
        }
        m->select(true);
        if (m_attack->sourceIds().isEmpty() && m->player()->id() == 1) {
            m_attack->beginnAttack(monsterId);
        } else if (m->player()->id() == 1) {
            m_attack->addMonsterId(monsterId);
        }
    }
}

void Board::resetSelections()
{
    foreach (Monster* monster, m_monsters->monsters()) {
        monster->select(false);
    }
    m_attack->reset();
}

void Board::resetBoard()
{
    qDebug() << "Clean up board.";

    // delete monsters
    foreach (Monster *monster, m_monsters->monsters()) {
        monster->deleteLater();
    }

    // delete players
    foreach (Player *player, m_players) {
        player->deleteLater();
    }

    m_level = 0;
    m_players.clear();
    emit playersChanged();
    m_monsters->clearModel();
    emit monstersChanged();
}

Monster *Board::createMonster(QVariantMap monsterJson)
{
    int id = monsterJson.value("id").toInt();
    QString monsterTypeString = monsterJson.value("monsterType").toString();
    QPoint position(monsterJson.value("x").toInt(), monsterJson.value("y").toInt());
    int startValue = monsterJson.value("startValue").toInt();
    int size = monsterJson.value("size").toInt();
    int playerId = monsterJson.value("player").toInt();

    qDebug() << "    -> Create Monster" << id << monsterTypeString;

    Monster *monster = new Monster(m_engine, Monster::MonsterTypeNormal, -1, startValue, QPoint(), "white", this);
    monster->setId(id);
    monster->setMonsterType(monsterTypeString);
    monster->setPosition(position);
    monster->setSize(size);

    foreach (Player* player, m_players) {
        if (player->id() == playerId) {
            monster->setPlayer(player);
        }
    }
    return monster;
}

Player *Board::createPlayer(QVariantMap playerJson)
{
    int id = playerJson.value("id").toInt();
    QString color = playerJson.value("color").toString();
    QString playerType = playerJson.value("playerType").toString();
    int strength =  playerJson.value("strength").toInt();
    int speed =  playerJson.value("speed").toInt();
    int reproduction =  playerJson.value("reproduction").toInt();
    int defense =  playerJson.value("defense").toInt();
    int reaction =  playerJson.value("reaction").toInt();

    qDebug() << "    -> Create Player" << id << playerType;

    Player* player = new Player(id, m_level);
    player->setColorString(color);
    player->setPlayerType(playerType);
    player->setStrength(strength);
    player->setSpeed(speed);
    player->setDefence(defense);
    player->setReproduction(reproduction);
    player->setReaction(reaction);

    return player;
}

void Board::attackFinished()
{
    if (m_attack->sourceIds().isEmpty())
        return;

    m_engine->startAttack(m_attack);
    m_attack->reset();
    resetSelections();
}
