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

#ifndef ATTACK_H
#define ATTACK_H

#include <QObject>
#include <QDebug>

class Attack : public QObject
{
    Q_OBJECT

public:
    explicit Attack(QObject *parent = 0);

    void beginnAttack(int id);
    void endAttack(int id);
    QList<int> sourceIds();
    int destinationId();
    void addMonsterId(int id);
    void reset();

private:
    QList<int> m_sourceIds;
    int m_destinationId;
    int m_currentId;

signals:
    void attackFinished();

};
#endif // ATTACK_H
