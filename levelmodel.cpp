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

#include "levelmodel.h"

LevelModel::LevelModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Level *> LevelModel::levels()
{
    return m_levels;
}

Level *LevelModel::level(int levelId)
{
    foreach (Level *level, m_levels) {
        if (level->levelId() == levelId) {
            return level;
        }
    }
    return NULL;
}

int LevelModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_levels.count();
}

QVariant LevelModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_levels.count())
        return QVariant();

    Level *level= m_levels.at(index.row());
    if (role == IdRole) {
        return level->levelId();
    } else if (role == TimeRole) {
        return level->bestTime();
    } else if (role == NameRole) {
        return level->name();
    } else if (role == UnlockedRole) {
        return level->unlocked();
    }
    return QVariant();
}

void LevelModel::addLevel(Level *level)
{
    beginInsertRows(QModelIndex(), m_levels.count(), m_levels.count());
    m_levels.append(level);
    connect(level, &Level::unlockedChanged, this, &LevelModel::unlockedChanged);
    connect(level, &Level::bestTimeChanged, this, &LevelModel::bestTimeChanged);
    endInsertRows();
    QModelIndex i = index(m_levels.indexOf(level));
    emit dataChanged(i, i);
}

QHash<int, QByteArray> LevelModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "levelId";
    roles[TimeRole] = "bestTime";
    roles[NameRole] = "levelName";
    roles[UnlockedRole] = "unlocked";
    return roles;
}

int LevelModel::indexOf(Level *level)
{
    return m_levels.indexOf(level);
}

void LevelModel::unlockedChanged()
{
    Level *level = qobject_cast<Level *>(sender());
    QModelIndex i = index(m_levels.indexOf(level));
    emit dataChanged(i, i, {UnlockedRole});
}

void LevelModel::bestTimeChanged()
{
    Level *level = qobject_cast<Level *>(sender());
    QModelIndex i = index(m_levels.indexOf(level));
    emit dataChanged(i, i, {TimeRole});
}
