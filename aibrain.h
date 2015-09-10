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

    Monster *sourceMonster();
    Monster *destinationMonster();

    int valueAfterImpact();
    int percentageAfterImpact();
    double distance();
    int canConquer();

private:
    Board *m_board;
    Monster *m_sourceMonsters;
    Monster *m_destinationMonster;

    double m_strengthStepWidth;
    double m_defenseStepWidth;

    int m_attackPoints;
    int m_valueAfterImpact;
    int m_percentageAfterImpact;
    double m_distance;
    int m_canConquer;

    double calculateDistance(Monster *a, Monster *b);
    int calculateDestinationPointsAfterAttack();
    int calculatePercentageAfterAttack();


};

bool compareDistance(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareSourceValue(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareDestinationValue(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareDestinationValueAfterImpact(VirtualAttack *attack1, VirtualAttack *attack2);
bool comparePercentageAfterImpact(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareConquere(VirtualAttack *attack1, VirtualAttack *attack2);

#endif // AIBRAIN_H
