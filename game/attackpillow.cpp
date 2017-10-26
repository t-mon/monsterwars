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

#include "attackpillow.h"
#include "player.h"
#include "monster.h"

AttackPillow::AttackPillow(Player *player, Monster *sourceMonster, Monster *destinationMonster, int count, int strength, int speed, QObject *parent):
    QObject(parent),
    m_id(QUuid::createUuid().toString()),
    m_player(player),
    m_sourceMonster(sourceMonster),
    m_destinationMonster(destinationMonster),
    m_count(count),
    m_strength(strength),
    m_speed(speed)
{
}

QString AttackPillow::id() const
{
    return m_id;
}

Player *AttackPillow::player() const
{
    return m_player;
}

Monster *AttackPillow::sourceMonster() const
{
    return m_sourceMonster;
}

Monster *AttackPillow::destinationMonster() const
{
    return m_destinationMonster;
}

int AttackPillow::count() const
{
    return m_count;
}

QString AttackPillow::colorString() const
{
    return m_player->colorString();
}

int AttackPillow::strength() const
{
    return m_strength;
}

int AttackPillow::speed() const
{
    return m_speed;
}

