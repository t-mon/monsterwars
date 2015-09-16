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

#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QColor>

#include "attackpillow.h"


class GameEngine;
class Player;
class Node;

class Monster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString colorString READ colorString NOTIFY colorStringChanged)
    Q_PROPERTY(QString monsterTypeString READ monsterTypeString CONSTANT)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(int value READ value NOTIFY valueChanged)
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool selected READ selected NOTIFY selectedChanged)

public:
    enum MonsterType{
        MonsterTypeNormal,
        MonsterTypeStrength,
        MonsterTypeReproduction,
        MonsterTypeDefense,
        MonsterTypeSpeed
    };

    explicit Monster(GameEngine *engine,
                   MonsterType monsterType = MonsterTypeNormal,
                   int id = -1,
                   int startValue = 0,
                   QPoint position = QPoint(),
                   QString colorString = "white",
                   QObject *parent = 0);

    Monster(GameEngine* engine, int startValue);

    void setMonsterType(const MonsterType &monsterType);
    bool setMonsterType(const QString &monsterType);

    MonsterType monsterType() const;
    QString monsterTypeString() const;

    void setPlayer(Player* player);
    Player *player() const;

    void setId(const int &id);
    int id() const;

    int value() const;

    int size() const;
    void setSize(const int &size);

    void setPosition(const QPoint &position);
    QPoint position() const;

    void setColorString(const QString &colorString);
    QString colorString() const;

    void select(const bool &selected);
    bool selected() const;

    int split();
    void impact(AttackPillow *attackPillow);

private:
    GameEngine *m_engine;
    MonsterType m_monsterType;
    QString m_monsterTypeString;
    int m_id;
    int m_value;
    int m_size;
    int m_maxValue;
    QPoint m_position;
    QString m_colorString;
    Player *m_player;
    bool m_selected;
    int m_tickCounter;

    QString monsterTypeToString(MonsterType monsterType);

signals:
    void valueChanged();
    void sizeChanged();
    void positionChanged();
    void colorStringChanged();
    void selectedChanged();
    void playerChanged();
    void impact();

private slots:
    void slotTick();
};
#endif // MONSTER_H
