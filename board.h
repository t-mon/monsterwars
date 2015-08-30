#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QQmlListProperty>
#include <QDebug>
#include <QHash>
#include <QGenericMatrix>

class GameEngine;
class Level;
class Player;
class Monster;
class Node;
class Attack;
class PathFinder;

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int columns READ columns NOTIFY boardChanged)
    Q_PROPERTY(int rows READ rows CONSTANT)
    Q_PROPERTY(int monsterCount READ monsterCount NOTIFY boardChanged)
    Q_PROPERTY(QQmlListProperty<Monster> monsters READ monsters NOTIFY boardChanged)
    Q_PROPERTY(QQmlListProperty<Player> players READ players NOTIFY boardChanged)

public:
    explicit Board(GameEngine *engine);

    void setLevel(Level *level);
    Level *level() const;
    QList<Node *> nodes();

    int rows() const;
    int columns() const;

    QQmlListProperty<Player> players();
    QQmlListProperty<Monster> monsters();

    QList<Player *> playersList();
    QList<Monster *> monstersList();


    int monsterCount() const;
    Q_INVOKABLE Monster *monster(int id) const;
    Q_INVOKABLE Player *player(int id) const;


    Q_INVOKABLE void evaluateReleased(const int &monsterId);
    Q_INVOKABLE void evaluateHovered(const bool &hovering, const int &monsterId);
    Q_INVOKABLE void resetSelections();

    void resetBoard();

signals:
    void boardChanged();
    void startAttack(Attack *attack);

private:
    GameEngine *m_engine;
    Level *m_level;

    QList<Monster *> m_monsters;
    QList<Player *> m_players;
    QList<Node *> m_nodes;

    Attack *m_attack;

    Monster *createMonster(QVariantMap monsterJson);
    Player *createPlayer(QVariantMap playerJson);

    void monsterChanged();

private slots:
    void attackFinished();
};

#endif // BOARD_H
