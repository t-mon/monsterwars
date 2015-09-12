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

#ifndef ATTACKPILLOW_H
#define ATTACKPILLOW_H

#include <QObject>
#include <QDebug>
#include <QColor>
#include <QUuid>

class Player;
class Monster;

class AttackPillow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(int speed READ speed CONSTANT)
    Q_PROPERTY(QString colorString READ colorString CONSTANT)

    Q_PROPERTY(Monster *sourceMonster READ sourceMonster CONSTANT)
    Q_PROPERTY(Monster *destinationMonster READ destinationMonster CONSTANT)

public:
    explicit AttackPillow(Player* player, Monster *sourceMonster, Monster *destinationMonster, int count, int strength, int speed, QObject *parent = 0);

    QString id() const;

    Player *player() const;
    Monster *sourceMonster() const;
    Monster *destinationMonster() const;

    int count() const;
    QString colorString() const;
    int strength() const;
    int speed() const;

private:
    QString m_id;
    Player *m_player;
    Monster *m_sourceMonster;
    Monster *m_destinationMonster;
    int m_count;
    int m_strength;
    int m_speed;

};
#endif // ATTACKPILLOW_H
