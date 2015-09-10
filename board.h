#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QQmlListProperty>
#include <QDebug>
#include <QHash>
#include <QGenericMatrix>

#include "monstermodel.h"

class GameEngine;
class Level;
class Player;
class Monster;
class Attack;

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int columns READ columns CONSTANT)
    Q_PROPERTY(int rows READ rows CONSTANT)
    Q_PROPERTY(int monsterCount READ monsterCount NOTIFY monstersChanged)
    Q_PROPERTY(MonsterModel *monsters READ monsters NOTIFY monstersChanged)
    Q_PROPERTY(QQmlListProperty<Player> players READ players NOTIFY playersChanged)

public:
    explicit Board(GameEngine *engine);

    void setLevel(Level *level);
    Level *level() const;
    QList<Node *> nodes();

    int rows() const;
    int columns() const;

    QTime gameTime() const;

    QQmlListProperty<Player> players();
    MonsterModel *monsters();

    QList<Player *> playersList();
    QList<Monster *> monstersList();

    QList<Monster *> myMonsters(Player *player);
    QList<Monster *> enemyMonsters(Player *player);
    QList<Monster *> freeMonsters();

    int monsterCount() const;
    Q_INVOKABLE Monster *monster(int id) const;
    Q_INVOKABLE Player *player(int id) const;

    Q_INVOKABLE void evaluateReleased(const int &monsterId);
    Q_INVOKABLE void evaluateHovered(const bool &hovering, const int &monsterId);
    Q_INVOKABLE void resetSelections();

    void resetBoard();

signals:
    void boardChanged();
    void monstersChanged();
    void playersChanged();
    void gameTimeChanged();
    void startAttack(Attack *attack);

private:
    Level *m_level;
    GameEngine *m_engine;

    MonsterModel *m_monsters;
    QList<Player *> m_players;

    Attack *m_attack;

    Monster *createMonster(QVariantMap monsterJson);
    Player *createPlayer(QVariantMap playerJson);

private slots:
    void attackFinished();

};

#endif // BOARD_H
