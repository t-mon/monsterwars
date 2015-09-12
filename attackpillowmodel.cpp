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

#include "attackpillowmodel.h"

#include "monster.h"

AttackPillowModel::AttackPillowModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<AttackPillow *> AttackPillowModel::pillows()
{
    return m_pillows;
}

int AttackPillowModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_pillows.count();
}

QVariant AttackPillowModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_pillows.count())
        return QVariant();

    AttackPillow *pillow = m_pillows.at(index.row());
    if (role == ValueRole) {
        return pillow->count();
    } else if (role == ColorStringRole) {
        return pillow->colorString();
    } else if (role == SpeedRole) {
        return pillow->speed();
    } else if (role == IdRole) {
        return pillow->id();
    } else if (role == SourceXRole) {
        return pillow->sourceMonster()->position().x();
    } else if (role == SourceYRole) {
        return pillow->sourceMonster()->position().y();
    } else if (role == DestinationXRole) {
        return pillow->destinationMonster()->position().x();
    } else if (role == DestinationYRole) {
        return pillow->destinationMonster()->position().y();
    }
    return QVariant();
}

void AttackPillowModel::addPillow(AttackPillow *pillow)
{
    beginInsertRows(QModelIndex(), m_pillows.count(), m_pillows.count());
    m_pillows.append(pillow);
    emit pillowListChanged();
    endInsertRows();
}

void AttackPillowModel::removePillow(AttackPillow *pillow)
{
    beginRemoveRows(QModelIndex(), indexOf(pillow), indexOf(pillow));
    m_pillows.removeAll(pillow);
    emit pillowListChanged();
    endRemoveRows();
}

void AttackPillowModel::clearModel()
{
    beginResetModel();
    m_pillows.clear();
    endResetModel();
}

QHash<int, QByteArray> AttackPillowModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    roles[ColorStringRole] = "colorString";
    roles[SpeedRole] = "speed";
    roles[IdRole] = "id";
    roles[SourceXRole] = "sourceX";
    roles[SourceYRole] = "sourceY";
    roles[DestinationXRole] = "destinationX";
    roles[DestinationYRole] = "destinationY";
    return roles;
}

int AttackPillowModel::indexOf(AttackPillow *pillow)
{
    return m_pillows.indexOf(pillow);
}
