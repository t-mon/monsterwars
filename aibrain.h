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

#ifndef AIBRAIN_H
#define AIBRAIN_H

#include <QObject>
#include <QTimer>

#include "board.h"
#include "player.h"
#include "monster.h"
#include "attack.h"

class AiBrain : public QObject
{
    Q_OBJECT
public:
    explicit AiBrain(Board *board, Player *player, double strengthStepWidth, double defenseStepWidth, QObject *parent = 0);
    void start();
    void stop();

private:
    Board *m_board;
    Player *m_player;
    QTimer *m_timer;
    Attack *m_attack;

    void calculateAttack();
    int calculateIntervall();

    double m_strengthStepWidth;
    double m_defenseStepWidth;

signals:
    void startAttack(Attack *attack);

private slots:
    void timeout();
};



class VirtualAttack
{
public:
    VirtualAttack(Board *board, Monster *sourceMonster, Monster *destinationMonster, double strengthStepWidth, double defenseStepWidth);
    VirtualAttack(Board *board, QList<Monster *>sourceMonsters, Monster *destinationMonster, double strengthStepWidth, double defenseStepWidth);

    QList<Monster *> sourceMonsters();
    Monster *destinationMonster();

    int sourcePoints();
    int valueAfterImpact();
    int percentageAfterImpact();
    double distance();
    int canConquer();

private:
    Board *m_board;
    QList<Monster *> m_sourceMonsters;
    Monster *m_destinationMonster;

    double m_strengthStepWidth;
    double m_defenseStepWidth;

    int m_attackPoints;
    int m_sourcePoints;
    int m_valueAfterImpact;
    int m_percentageAfterImpact;
    double m_distance;
    int m_canConquer;

    double calculateDistance();
    int calculateDestinationPointsAfterAttack();
    int calculatePercentageAfterAttack();

};

bool compareMonsterValue(Monster *monster1, Monster *monster2);

bool compareDistance(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareSourceValue(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareDestinationValue(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareDestinationSize(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareDestinationValueAfterImpact(VirtualAttack *attack1, VirtualAttack *attack2);
bool comparePercentageAfterImpact(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareConquere(VirtualAttack *attack1, VirtualAttack *attack2);

#endif // AIBRAIN_H
