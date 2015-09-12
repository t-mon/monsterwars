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

#ifndef MONSTERMODEL_H
#define MONSTERMODEL_H

#include <QAbstractListModel>

#include "monster.h"

class MonsterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MonsterRole {
        IdRole,
        ValueRole,
        ColorStringRole,
        MonsterTypeRole,
        SizeRole,
        PositionXRole,
        PositionYRole,
        SelectedRole
    };

    explicit MonsterModel(QObject *parent = 0);

    QList<Monster *> monsters();
    Monster *monsterWithId(int id);

    void impact(Monster *monster, AttackPillow *pillow);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addMonster(Monster *monster);
    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Monster *> m_monsters;
    int indexOf(Monster *monster);

private slots:
    void monsterValueChanged();
    void monsterColorChanged();
    void monsterSelectedChanged();
};

#endif // MONSTERMODEL_H
