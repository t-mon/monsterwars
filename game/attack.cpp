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

#include "attack.h"

Attack::Attack(QObject *parent):
    QObject(parent)
{
}

void Attack::beginnAttack(int id)
{
    m_sourceIds.append(id);
}

void Attack::endAttack(int id)
{
    for (int i = 0; i < m_sourceIds.count(); i++) {
        if (m_sourceIds.at(i) == id) {
            m_sourceIds.removeAt(i);
        }
    }
    m_destinationId = id;
    emit attackFinished();
}

QList<int> Attack::sourceIds()
{
    return m_sourceIds;
}

int Attack::destinationId()
{
    return m_destinationId;
    emit attackFinished();
}

void Attack::removeSourceId(int id)
{
    m_sourceIds.removeAll(id);
}

void Attack::addMonsterId(int id)
{
    if(m_sourceIds.contains(id))
        return;

    m_sourceIds.append(id);
}

void Attack::reset()
{
    m_sourceIds.clear();
    m_destinationId = -1;
}
