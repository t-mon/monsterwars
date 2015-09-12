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
    emit nameChanged();
}

QString Level::name() const
{
    return m_name;
}

void Level::setLevelId(const int &levelId)
{
    m_levelId = levelId;
    emit levelIdChanged();
}

int Level::levelId() const
{
    return m_levelId;
}

void Level::setMonstersVariants(const QVariantList &monstersVariant)
{
    m_monstersVariant = monstersVariant;
}

QVariantList Level::monstersVariant() const
{
    return m_monstersVariant;
}

void Level::setPlayersVariants(const QVariantList &playersVariant)
{
    m_playersVariant = playersVariant;
}

QVariantList Level::playersVariant() const
{
    return m_playersVariant;
}

