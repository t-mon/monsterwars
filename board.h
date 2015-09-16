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
    Q_PROPERTY(int levelId READ levelId NOTIFY levelIdChanged)
    Q_PROPERTY(MonsterModel *monsters READ monsters NOTIFY monstersChanged)
    Q_PROPERTY(QQmlListProperty<Player> players READ players NOTIFY playersChanged)

public:
    explicit Board(GameEngine *engine);

    void setLevel(Level *level);
    Level *level() const;
    int levelId() const;
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
    void levelIdChanged();
    void startAttack(Attack *attack);

private:
    Level *m_level;
    GameEngine *m_engine;

    MonsterModel *m_monsters;
    QList<Player *> m_players;

    Attack *m_attack;

    Monster *createMonster(QVariantMap monsterJson);
    Player *createPlayer(QVariantMap playerJson);

    int m_levelId;

private slots:
    void attackFinished();

};

#endif // BOARD_H
