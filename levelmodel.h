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

#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#include <QAbstractListModel>
#include <QSettings>

#include "level.h"

class LevelModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PillowRole {
        IdRole = Qt::DisplayRole,
        UnlockedRole,
        TimeRole,
        NameRole
    };
    explicit LevelModel(QObject *parent = 0);

    QList<Level *> levels();
    Q_INVOKABLE Level *level(int levelId);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addLevel(Level* level);
    void resetLevelSettings();
    void sortLevels();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Level *> m_levels;

    int indexOf(Level *level);

private slots:
    void unlockedChanged();
    void bestTimeChanged();
};

bool compareLevel(Level *level1, Level *level2);


#endif // LEVELMODEL_H
