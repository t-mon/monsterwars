#include "board.h"
#include "level.h"
#include "gameengine.h"
#include "node.h"
#include "monster.h"
#include "player.h"
#include "attack.h"
#include "math.h"


#include <QJsonDocument>

Board::Board(GameEngine *engine):
    QObject(engine),
    m_level(0),
    m_engine(engine)
{    
    m_attack = new Attack(this);
    connect(m_attack, &Attack::attackFinished, this, &Board::attackFinished);
}

void Board::setLevel(Level *level)
{
    resetBoard();
    m_level = level;

    qDebug() << "loaded " << m_level->name() << "on board...";

    foreach (const QVariant &playerJson, m_level->playersVariant()) {
        m_players.append(createPlayer(playerJson.toMap()));
    }

    // add the dummy player from type PlayerTypeNone (id 0)
    Player *player = new Player(0, m_level);
    m_players.append(player);
    emit playersChanged();

    foreach (const QVariant &monsterJson, m_level->monstersVariant()) {
        m_monsters.append(createMonster(monsterJson.toMap()));
    }
    emit monstersChanged();
    resetSelections();
}

Level *Board::level() const
{
    return m_level;
}

QQmlListProperty<Monster> Board::monsters()
{
    return QQmlListProperty<Monster>(this, m_monsters);
}

QList<Player *> Board::playersList()
{
    return m_players;
}

QList<Monster *> Board::monstersList()
{
    return m_monsters;
}

QQmlListProperty<Player> Board::players()
{
    return QQmlListProperty<Player>(this, m_players);
}

int Board::rows() const
{
    return m_engine->rows();
}

int Board::columns() const
{
    return m_engine->columns();
}

QList<Node *> Board::nodes()
{
    return  m_nodes;
}

int Board::monsterCount() const
{
    return m_monsters.count();
}

Monster *Board::monster(int id) const
{
    foreach (Monster *monster, m_monsters) {
        if(monster->id() == id){
            return monster;
        }
    }
    return NULL;
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
        m_attack->endAttack(m->id());
    }
}

void Board::evaluateHovered(const bool &hovering, const int &monsterId)
{
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
    foreach (Monster* monster, m_monsters) {
        monster->select(false);
    }
    m_attack->reset();
}

void Board::resetBoard()
{
    qDebug() << "Clean up board.";

    // delete monsters
    foreach (Monster *monster, m_monsters) {
        monster->deleteLater();
    }

    // delete players
    foreach (Player *player, m_players) {
        player->deleteLater();
    }

    m_level = 0;
    m_players.clear();
    emit playersChanged();
    m_monsters.clear();
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

    connect(monster, &Monster::playerChanged, this, &Board::monstersChanged);
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

    qDebug() << "    -> Create Player" << id << playerType;

    Player* player = new Player(id, m_level);
    player->setColorString(color);
    player->setPlayerType(playerType);
    player->setStrength(strength);
    player->setSpeed(speed);
    player->setDefence(defense);
    player->setReproduction(reproduction);

    return player;
}

void Board::attackFinished()
{
    if (m_attack->sourceIds().isEmpty())
        return;

    qDebug() << "Attack -> " << m_attack->sourceIds() << " -> " << m_attack->destinationId();

    emit startAttack(m_attack);
    m_attack->reset();
    resetSelections();
}
