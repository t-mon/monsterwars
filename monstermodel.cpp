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

#include "monstermodel.h"

MonsterModel::MonsterModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Monster *> MonsterModel::monsters()
{
    return m_monsters;
}

Monster *MonsterModel::monsterWithId(int id)
{
    foreach (Monster *monster, m_monsters) {
        if (monster->id() == id) {
            return monster;
        }
    }
    return NULL;
}

void MonsterModel::impact(Monster *monster, AttackPillow *pillow)
{
    monster->impact(pillow);
}

int MonsterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_monsters.count();
}

QVariant MonsterModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_monsters.count())
        return QVariant();

    Monster *monster= m_monsters.at(index.row());
    if (role == IdRole) {
        return monster->id();
    } else if (role == ValueRole) {
        return monster->value();
    } else if (role == ColorStringRole) {
        return monster->colorString();
    } else if (role == MonsterTypeRole) {
        return monster->monsterTypeString();
    } else if (role == SizeRole) {
        return monster->size();
    } else if (role == PositionXRole) {
        return monster->position().x();
    } else if (role == PositionYRole) {
        return monster->position().y();
    } else if (role == SelectedRole) {
        return monster->selected();
    }
    return QVariant();
}

void MonsterModel::addMonster(Monster *monster)
{
    beginInsertRows(QModelIndex(), m_monsters.count(), m_monsters.count());
    m_monsters.append(monster);
    connect(monster, &Monster::valueChanged, this, &MonsterModel::monsterValueChanged);
    connect(monster, &Monster::selectedChanged, this, &MonsterModel::monsterSelectedChanged);
    connect(monster, &Monster::colorStringChanged, this, &MonsterModel::monsterColorChanged);
    endInsertRows();

    QModelIndex i = index(m_monsters.indexOf(monster));
    emit dataChanged(i, i);
}

void MonsterModel::clearModel()
{
    beginResetModel();
    m_monsters.clear();
    endResetModel();
}

QHash<int, QByteArray> MonsterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "monsterId";
    roles[ValueRole] = "monsterValue";
    roles[ColorStringRole] = "monsterColor";
    roles[MonsterTypeRole] = "monsterType";
    roles[SizeRole] = "monsterSize";
    roles[PositionXRole] = "positionX";
    roles[PositionYRole] = "positionY";
    roles[SelectedRole] = "selected";
    return roles;
}

void MonsterModel::monsterValueChanged()
{
    Monster *monster = qobject_cast<Monster *>(sender());
    QModelIndex i = index(m_monsters.indexOf(monster));
    emit dataChanged(i, i, {ValueRole});
}

void MonsterModel::monsterColorChanged()
{
    Monster *monster = qobject_cast<Monster *>(sender());
    QModelIndex i = index(m_monsters.indexOf(monster));
    emit dataChanged(i, i, {ColorStringRole});
}

void MonsterModel::monsterSelectedChanged()
{
    Monster *monster = qobject_cast<Monster *>(sender());
    QModelIndex i = index(m_monsters.indexOf(monster));
    emit dataChanged(i, i, {SelectedRole});
}
