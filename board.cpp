#include "board.h"
#include "level.h"
#include "gameengine.h"
#include "node.h"
#include "monster.h"
#include "player.h"
#include "attack.h"
#include "pathfinder.h"
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

void Board::setLevel(const QVariantMap &levelDescription)
{
    resetBoard();
    m_level = new Level(this);
    m_level->setName(levelDescription.value("name").toString());
    QVariantList players = levelDescription.value("players").toList();
    foreach (const QVariant &playerJson, players) {
        Player* player = createPlayer(playerJson.toMap());
        m_level->addPlayer(player);
    }

    // add the dummy player from type PlayerTypeNone (id 0)
    Player *player = new Player(0, m_level);
    m_level->addPlayer(player);

    QVariantList monsteres = levelDescription.value("monsteres").toList();
    foreach (const QVariant &monsterJson, monsteres) {
        Monster* monster = createMonster(monsterJson.toMap());
        m_level->addMonster(monster);
    }

    m_players = m_level->players();
    m_monsteres = m_level->monsteres();

    qDebug() << "loaded " << m_level->name() << "on board...";

    //calculateMonsterNodes();
    resetSelections();
    emit boardChanged();
}

void Board::createBoard()
{
    //createNodes();
    m_pathFinder = new PathFinder(this);

}

Level *Board::level() const
{
    return m_level;
}

QQmlListProperty<Monster> Board::monsteres()
{
    return QQmlListProperty<Monster>(this, m_monsteres);
}

int Board::nodeCount() const
{
    return m_nodes.count();
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
    return m_level->monsteres().count();
}

Monster *Board::monster(int id) const
{
    return m_level->monster(id);
}

void Board::evaluateReleased(const int &monsterId)
{
    Monster* monster = m_level->monster(monsterId);
    monster->select(true);
    if (m_attack->sourceIds().isEmpty()) {
        m_attack->beginnAttack(monster->id());
    } else {
        m_attack->endAttack(monster->id());
    }
}

void Board::evaluateHovered(const bool &hovering, const int &monsterId)
{
    Monster* monster = m_level->monster(monsterId);
    if (!hovering) {
        if (monster->player()->id() != 1) {
            monster->select(false);
        }
    }
    if (hovering) {
        if (m_attack->sourceIds().isEmpty() && monster->player()->id() != 1) {
            return;
        }
        monster->select(true);
        if (m_attack->sourceIds().isEmpty() && monster->player()->id() == 1) {
            m_attack->beginnAttack(monsterId);
        } else if (monster->player()->id() == 1) {
            m_attack->addMonsterId(monsterId);
        }
    }
}

void Board::resetSelections()
{
    foreach (Monster* monster, m_level->monsteres()) {
        monster->select(false);
    }
    m_attack->reset();
}

Node *Board::nodeAt(int x, int y) const
{
    int index = y * columns() + x;
    return nodeAt(index);
}

void Board::createNodes()
{
    // create all nodes
    int number = 0;
    for (int row = 0; row < rows(); row++) {
        for (int column = 0; column < columns(); column++) {
            Node *node = new Node(column, row, number, this);
            m_nodes.append(node);
            number++;
        }
    }

    // first row
    for (int i = 0; i < columns(); i++) {
        Node *currentNode = m_nodes.at(i);
        currentNode->setNorthEastNode(0);
        currentNode->setNorthNode(0);
        currentNode->setNorthWestNode(0);

        if (currentNode->number() == 0){   // first node in row
            currentNode->setWestNode(0);
            currentNode->setSouthWestNode(0);
            currentNode->setSouthNode(nodeAt(columns()));
            currentNode->setSouthEastNode(nodeAt(columns() + 1));
            currentNode->setEastNode(nodeAt(i + 1));
            continue;
        } else if (currentNode->number() == columns()) {        // last node in row
            currentNode->setWestNode(nodeAt(i - 1));
            currentNode->setSouthWestNode(nodeAt(i + columns() - 1));
            currentNode->setSouthNode(nodeAt(i + columns()));
            currentNode->setSouthEastNode(0);
            currentNode->setEastNode(0);

            continue;
        } else {                                                // every node between first and last
            currentNode->setWestNode(nodeAt(i - 1));
            currentNode->setSouthWestNode(nodeAt(i + columns()));
            currentNode->setSouthNode(nodeAt(i + columns()));
            currentNode->setSouthEastNode(nodeAt(i + columns() + 1));
            currentNode->setEastNode(nodeAt(i + 1));
            continue;
        }
        m_nodes.replace(i, currentNode);
    }

    // every row between the first and the last
    for (int j = 1; j < (rows() - 1); j++){
        for (int i = j * columns(); i < j * columns() + columns(); i++) {
            Node *currentNode = m_nodes.at(i);
            if (currentNode->number() == j * columns()){   // first node in row
                currentNode->setNorthEastNode(nodeAt(i - columns() + 1));
                currentNode->setNorthNode(nodeAt(i - columns()));
                currentNode->setNorthWestNode(0);
                currentNode->setWestNode(0);
                currentNode->setSouthWestNode(0);
                currentNode->setSouthNode(nodeAt(i + columns()));
                currentNode->setSouthEastNode(nodeAt(i + columns() + 1));
                currentNode->setEastNode(nodeAt(i + 1));
                continue;
            } else if (currentNode->number() == j * columns() + columns() -1) {        // last node in row
                currentNode->setNorthEastNode(0);
                currentNode->setNorthNode(nodeAt(i - columns()));
                currentNode->setNorthWestNode(nodeAt(i - columns() - 1));
                currentNode->setWestNode(nodeAt(i - 1));
                currentNode->setSouthWestNode(nodeAt(i + columns() - 1));
                currentNode->setSouthNode(nodeAt(i + columns()));
                currentNode->setSouthEastNode(0);
                currentNode->setEastNode(0);
                continue;
            } else {                                                // every node between first and last
                currentNode->setNorthEastNode(nodeAt(i - columns() + 1));
                currentNode->setNorthNode(nodeAt(i - columns()));
                currentNode->setNorthWestNode(nodeAt(i - columns() - 1));
                currentNode->setWestNode(nodeAt(i - 1));
                currentNode->setSouthWestNode(nodeAt(i + columns() - 1));
                currentNode->setSouthNode(nodeAt(i + columns()));
                currentNode->setSouthEastNode(nodeAt(i + columns() + 1));
                currentNode->setEastNode(nodeAt(i+1));
                continue;
            }
        }
    }

    // last row
    for (int i = (rows() - 1) * columns(); i < rows() * columns(); i++) {
        Node *currentNode = m_nodes.at(i);
        currentNode->setSouthEastNode(0);
        currentNode->setSouthNode(0);
        currentNode->setSouthWestNode(0);

        if (currentNode->number() == (rows() - 1) * columns()){   // first node in last row
            currentNode->setWestNode(0);
            currentNode->setNorthWestNode(0);
            currentNode->setNorthNode(nodeAt(i - columns()));
            currentNode->setNorthEastNode(nodeAt(i - columns() + 1));
            currentNode->setEastNode(nodeAt(i + 1));
            continue;
        } else if (currentNode->number() == rows() * columns() -1) {        // last node
            currentNode->setWestNode(nodeAt(i - 1));
            currentNode->setNorthWestNode(nodeAt(i - columns() - 1));
            currentNode->setNorthNode(nodeAt(i - columns()));
            currentNode->setNorthEastNode(0);
            currentNode->setEastNode(0);
            continue;
        } else {                                                // every node between first and last
            currentNode->setWestNode(nodeAt(i - 1));
            currentNode->setNorthWestNode(nodeAt(i - columns() - 1));
            currentNode->setNorthNode(nodeAt(i - columns()));
            currentNode->setNorthEastNode(nodeAt(i - columns() + 1));
            currentNode->setEastNode(nodeAt(i + 1));
            continue;
        }
    }
    qDebug() << "board nodes created...";
}

Node *Board::nodeAt(int number) const
{
    return m_nodes.at(number);
}

void Board::resetBoard()
{
    if(m_level){
        m_level->deleteLater();
    }

    foreach (Node* node, m_nodes) {
        node->setMonster(0);
    }
}

void Board::calculateMonsterNodes()
{
    m_monsteresNodes.clear();
    foreach (Monster *monster, m_monsteres) {
        // search the nodes in the monster radius
        for (int i = monster->position().x() - monster->size(); i <= monster->position().x() + monster->size(); i++) {
            for (int j = monster->position().y() - monster->size(); j <= monster->position().y() + monster->size(); j++) {
                int dx = monster->position().x() - i;
                int dy = monster->position().y() - j;
                double r = sqrt(pow(dx, 2) + pow(dy, 2));
                if(r <= monster->size() - 0.7) {
                    Node* node = nodeAt(i, j);
                    node->setMonster(monster);
                    m_monsteresNodes.insert(node->number(), monster);
                }
            }
        }
    }
}

Monster *Board::createMonster(QVariantMap monsterJson)
{
    int id = monsterJson.value("id").toInt();
    QString monsterTypeString = monsterJson.value("monsterType").toString();
    QPoint position(monsterJson.value("x").toInt(), monsterJson.value("y").toInt());
    int startValue = monsterJson.value("startValue").toInt();
    int size = monsterJson.value("size").toInt();
    int playerId = monsterJson.value("player").toInt();

    Monster *monster = new Monster(m_engine, startValue);
    monster->setId(id);
    monster->setMonsterType(monsterTypeString);
    monster->setPosition(position);
    monster->setSize(size);

    foreach (Player* player, m_level->players()) {
        if (player->id() == playerId) {
            monster->setPlayer(player);
        }
    }

    connect(monster, &Monster::playerChanged, this, &Board::monsterChanged);
    return monster;
}

Player *Board::createPlayer(QVariantMap playerJson)
{
    int id = playerJson.value("id").toInt();
    QColor color = QColor(playerJson.value("color").toString());
    QString playerType = playerJson.value("playerType").toString();
    int strength =  playerJson.value("strength").toInt();
    int speed =  playerJson.value("speed").toInt();
    int reproduction =  playerJson.value("reproduction").toInt();
    int defense =  playerJson.value("defense").toInt();

    Player* player = new Player(id, m_level);
    player->setColor(color);
    player->setPlayerType(playerType);
    player->setStrength(strength);
    player->setSpeed(speed);
    player->setDefence(defense);
    player->setReproduction(reproduction);

    return player;
}

void Board::monsterChanged()
{
    Monster* monster = static_cast<Monster*>(sender());

    foreach (int nodeId, m_monsteresNodes.keys(monster)) {
        Node* node = nodeAt(nodeId);
        node->setMonster(monster);
    }
}

void Board::attackFinished()
{
    if (m_attack->sourceIds().isEmpty()) {
        return;
    }
    qDebug() << "perform attack -> " << m_attack->sourceIds() << "        --->     " << m_attack->destinationId();
//    foreach (int id, m_attack->sourceIds()) {
//        m_pathFinder->calculatePath(m_level->monster(id), m_level->monster(m_attack->destinationId()));
//    }



    emit startAttack(m_attack);
    m_attack->reset();
    resetSelections();
}
