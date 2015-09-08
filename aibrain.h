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

    double percentage();
    double distance();

private:
    Monster *m_sourceMonsters;
    Monster *m_destinationMonster;
    double m_percentage;
    double m_distance;

    double distanceBetweenMonsters(Monster *a, Monster *b);

};

#endif // AIBRAIN_H
