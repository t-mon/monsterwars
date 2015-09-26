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

#ifndef ATTACKPILLOWMODEL_H
#define ATTACKPILLOWMODEL_H

#include <QAbstractListModel>

#include "attackpillow.h"

class AttackPillowModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PillowRole {
        ValueRole = Qt::DisplayRole,
        ColorStringRole,
        SpeedRole,
        IdRole,
        SourceXRole,
        SourceYRole,
        DestinationXRole,
        DestinationYRole
    };

    explicit AttackPillowModel(QObject *parent = 0);

    QList<AttackPillow *> pillows();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addPillow(AttackPillow *pillow);
    void removePillow(AttackPillow *pillow);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<AttackPillow *> m_pillows;
    int m_stepSize;
    int m_currentItemIdex;

    int indexOf(AttackPillow *pillow);

signals:
    void pillowListChanged();

};

#endif // ATTACKPILLOWMODEL_H
