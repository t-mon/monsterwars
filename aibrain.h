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
    explicit AiBrain(Board *board, Player *player, QObject *parent = 0);
    void start();
    void stop();

private:
    Board *m_board;
    Player *m_player;
    QTimer *m_timer;
    Attack *m_attack;

    void calculateAttack();
    int calculateIntervall();

signals:
    void startAttack(Attack *attack);

private slots:
    void timeout();
};


class VirtualAttack
{
public:
    VirtualAttack(Monster *sourceMonster, Monster *destinationMonster);

    Monster *sourceMonster();
    Monster *destinationMonster();

    int points();
    double distance();

private:
    Monster *m_sourceMonsters;
    Monster *m_destinationMonster;

    int m_points;
    double m_distance;

    double calculateDistance(Monster *a, Monster *b);
    int calculatePoints();




};

bool compareDistance(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareSourceValue(VirtualAttack *attack1, VirtualAttack *attack2);
bool compareDestinationValue(VirtualAttack *attack1, VirtualAttack *attack2);

#endif // AIBRAIN_H
