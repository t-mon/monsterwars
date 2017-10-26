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

#include "aibrain.h"
#include "math.h"

AiBrain::AiBrain(Board *board, Player *player, double strengthStepWidth, double defenseStepWidth, QObject *parent) :
    QObject(parent),
    m_board(board),
    m_player(player),
    m_strengthStepWidth(strengthStepWidth),
    m_defenseStepWidth(defenseStepWidth)
{
    m_attack = new Attack(this);
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &AiBrain::timeout);
}

void AiBrain::start()
{
    qsrand(qrand());
    m_timer->setInterval(qrand() % ((5000 + 1) - 4000) + 4000);
    m_timer->start();
}

void AiBrain::stop()
{
    m_timer->stop();
}

void AiBrain::calculateAttack()
{
    QList<Monster *> myMonsters = m_board->myMonsters(m_player);
    QList<Monster *> enemyMonsters = m_board->enemyMonsters(m_player);
    QList<Monster *> freeMonsters = m_board->freeMonsters();

    QList<VirtualAttack *> possibleAttacks;

    // check all possible single attacks
    foreach (Monster *myMonster, myMonsters) {
        foreach (Monster *enemyMonster, enemyMonsters) {
            possibleAttacks.append(new VirtualAttack(m_board, myMonster, enemyMonster, m_strengthStepWidth, m_defenseStepWidth));
        }
        foreach (Monster *freeMonster, freeMonsters) {
            possibleAttacks.append(new VirtualAttack(m_board, myMonster, freeMonster, m_strengthStepWidth, m_defenseStepWidth));
        }
    }

    // check multiple attacks
    if (myMonsters.count() >= 2) {
        QList<Monster *> multipleAttackMonsters;
        // take the two monsters with the highest count
        std::sort(myMonsters.begin(), myMonsters.end(), compareMonsterValue);
        multipleAttackMonsters.append(myMonsters.at(0));
        multipleAttackMonsters.append(myMonsters.at(1));
        foreach (Monster *enemyMonster, enemyMonsters) {
            possibleAttacks.append(new VirtualAttack(m_board, multipleAttackMonsters, enemyMonster, m_strengthStepWidth, m_defenseStepWidth));
        }
    }

    qDebug() << QString("Player %1: possible attacks -> %2").arg(m_player->id()).arg(possibleAttacks.count());

    if (possibleAttacks.isEmpty())
        return;

    // get the best attack of each heuristic
    QList<VirtualAttack *> bestOfEachHeuristic;

    // get shortest distance attack
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), compareDistance);
    VirtualAttack *shortestDistanceAttack = possibleAttacks.first();
    bestOfEachHeuristic.append(shortestDistanceAttack);

    // get attack with highest pillow value
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), compareSourceValue);
    VirtualAttack *highestSourceAttack = possibleAttacks.first();
    bestOfEachHeuristic.append(highestSourceAttack);

    // weakest enemy attack
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), compareDestinationValue);
    VirtualAttack *weakestTargetAttack = possibleAttacks.first();
    bestOfEachHeuristic.append(weakestTargetAttack);

    // smallest destination value after attack
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), compareDestinationValueAfterImpact);
    VirtualAttack *smallestTargetValueAttack = possibleAttacks.first();
    bestOfEachHeuristic.append(smallestTargetValueAttack);

    // highest percentage after attack
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), comparePercentageAfterImpact);
    VirtualAttack *highestPercentageValueAttack = possibleAttacks.first();
    bestOfEachHeuristic.append(highestPercentageValueAttack);

    // size of target monster
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), compareDestinationSize);
    VirtualAttack *biggestTargetAttack = possibleAttacks.first();
    bestOfEachHeuristic.append(biggestTargetAttack);

    // monster can be conquerd
    std::sort(possibleAttacks.begin(), possibleAttacks.end(), compareConquere);
    VirtualAttack *canConquerAttack = possibleAttacks.first();
    // add it twice to because conquer is verry important
    bestOfEachHeuristic.append(canConquerAttack);
    bestOfEachHeuristic.append(canConquerAttack);


    // check which attack is the best in most heuristics
    int totalHeuristicCount = bestOfEachHeuristic.count();
    int heuristicCount = 0;
    VirtualAttack *bestAttack = 0;
    while (!bestOfEachHeuristic.isEmpty()) {
        VirtualAttack *attack = bestOfEachHeuristic.first();
        int count = bestOfEachHeuristic.removeAll(attack);
        if (count >= heuristicCount) {
            bestAttack = attack;
            heuristicCount = count;
        }
    }

    if (!bestAttack) {
        qDeleteAll(possibleAttacks);
        return;
    }

    qDebug() << QString("Player %1: Best turn heuristic ratio: %2%").arg(m_player->id()).arg(qRound(heuristicCount * 100.0 / totalHeuristicCount));

    // create attack
    m_attack->reset();
    foreach (Monster *sourceMonster, bestAttack->sourceMonsters()) {
        m_attack->addMonsterId(sourceMonster->id());
    }
    m_attack->endAttack(bestAttack->destinationMonster()->id());

    // perform attack
    emit startAttack(m_attack);

    qDeleteAll(possibleAttacks);
}

int AiBrain::calculateIntervall()
{
    qsrand(qrand());
    int reactionValue = (8 - m_player->reaction()) * 500;
    int min = 4000 + reactionValue;
    int max = 8000 + reactionValue;
    return qrand() % ((max + 1) - min) + min;
}

void AiBrain::timeout()
{
    calculateAttack();
    m_timer->setInterval(calculateIntervall());
    qDebug() << QString("Player %1: Next turn in: %2 [ms]").arg(m_player->id()).arg(m_timer->interval());
}

VirtualAttack::VirtualAttack(Board *board, Monster *sourceMonster, Monster *destinationMonster, double strengthStepWidth, double defenseStepWidth) :
    m_board(board),
    m_sourceMonsters(QList<Monster *>() << sourceMonster),
    m_destinationMonster(destinationMonster),
    m_strengthStepWidth(strengthStepWidth),
    m_defenseStepWidth(defenseStepWidth)
{
    m_distance = calculateDistance();
    m_valueAfterImpact = calculateDestinationPointsAfterAttack();
    m_percentageAfterImpact = calculatePercentageAfterAttack();
}

VirtualAttack::VirtualAttack(Board *board, QList<Monster *> sourceMonsters, Monster *destinationMonster, double strengthStepWidth, double defenseStepWidth) :
    m_board(board),
    m_sourceMonsters(sourceMonsters),
    m_destinationMonster(destinationMonster),
    m_strengthStepWidth(strengthStepWidth),
    m_defenseStepWidth(defenseStepWidth)
{
    m_distance = calculateDistance();
    m_valueAfterImpact = calculateDestinationPointsAfterAttack();
    m_percentageAfterImpact = calculatePercentageAfterAttack();
}

QList<Monster *> VirtualAttack::sourceMonsters()
{
    return m_sourceMonsters;
}

Monster *VirtualAttack::destinationMonster()
{
    return m_destinationMonster;
}

int VirtualAttack::sourcePoints()
{
    int points = 0;
    foreach (Monster *sourceMonster, m_sourceMonsters) {
        points += sourceMonster->value();
    }
    return points;
}

int VirtualAttack::valueAfterImpact()
{
    return m_valueAfterImpact;
}

int VirtualAttack::percentageAfterImpact()
{
    return m_percentageAfterImpact;
}

double VirtualAttack::distance()
{
    return m_distance;
}

int VirtualAttack::canConquer()
{
    return m_canConquer;
}

double VirtualAttack::calculateDistance()
{
    double distance = 0;
    foreach (Monster * sourceMonster, m_sourceMonsters) {
        double dx = sourceMonster->position().x() - m_destinationMonster->position().x();
        double dy = sourceMonster->position().y() - m_destinationMonster->position().y();
        distance += sqrt(pow(dx,2) + pow(dy,2));
    }
    return distance / m_sourceMonsters.count();
}

int VirtualAttack::calculateDestinationPointsAfterAttack()
{
    int totalAttackPoints = 0;

    foreach (Monster *sourceMonster, m_sourceMonsters) {
        int attackPoints = sourceMonster->value() / 2;

        double strengthMultiplicator = 1 + (sourceMonster->player()->strength() * m_strengthStepWidth);
        // check if source monster is a strength monster
        if (sourceMonster->monsterType() == Monster::MonsterTypeStrength) {
            strengthMultiplicator += 4 * m_strengthStepWidth;
        }

        double defenseMultiplicator = 1 - (destinationMonster()->player()->defense() * m_defenseStepWidth);
        // check if destination monster is a defense monster
        if (destinationMonster()->monsterType() == Monster::MonsterTypeDefense) {
            defenseMultiplicator -= 4 * m_defenseStepWidth;
        }

        double finalMiltiplicator = (strengthMultiplicator + defenseMultiplicator) / 2;
        totalAttackPoints += qRound(attackPoints * finalMiltiplicator);
    }

    int valueAfterImpact = destinationMonster()->value() - totalAttackPoints;
    if(valueAfterImpact < 0) {
        //qDebug() << "This attack ("  << sourceMonster()->id() << "->" << destinationMonster()->id() << ") would conquer the monster.";
        m_canConquer = 100;
    } else {
        m_canConquer = 0;
    }

    return valueAfterImpact;
}

int VirtualAttack::calculatePercentageAfterAttack()
{
    QHash<Player *, int> points;
    // get all player points
    foreach (Player *player, m_board->playersList()) {
        int playerPoints = 0;
        foreach (Monster *monster, m_board->monstersList()) {
            if (monster->player()->id() == player->id()) {
                playerPoints += monster->value();
            }
        }
        points.insert(player, playerPoints);
    }

    Player *myPlayer = sourceMonsters().first()->player();
    Player *enemyPlayer = destinationMonster()->player();

    // manipulate points for new percentage
    int myPoints = points.take(myPlayer);
    int enemyPoints = points.take(enemyPlayer);

    myPoints -= m_attackPoints;

    // if conquer...
    if (m_attackPoints < 0) {
        myPoints += abs(m_valueAfterImpact);
        enemyPoints -= destinationMonster()->value();
    } else {
        enemyPoints = enemyPoints - destinationMonster()->value() + m_valueAfterImpact;
    }

    points.insert(myPlayer, myPoints);
    points.insert(enemyPlayer, enemyPoints);

    int totalPoints = 0;
    foreach (int value, points) {
        totalPoints += value;
    }

    // calculate new percentage
    return qRound((double)points.value(myPlayer) * 100 / totalPoints);
}

bool compareDistance(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->distance() < attack2->distance();
}

bool compareSourceValue(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->sourcePoints() > attack2->sourcePoints();
}

bool compareDestinationValue(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->destinationMonster()->value() < attack2->destinationMonster()->value();
}

bool compareDestinationValueAfterImpact(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->valueAfterImpact() < attack2->valueAfterImpact();
}

bool comparePercentageAfterImpact(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->percentageAfterImpact() > attack2->percentageAfterImpact();
}

bool compareConquere(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->canConquer() > attack2->canConquer();
}

bool compareDestinationSize(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->destinationMonster()->size() > attack2->destinationMonster()->size();
}

bool compareMonsterValue(Monster *monster1, Monster *monster2)
{
    return monster1->value() > monster2->value();
}
