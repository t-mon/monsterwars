#include "aibrain.h"
#include "math.h"

AiBrain::AiBrain(Board *board, Player *player, QObject *parent) :
    QObject(parent),
    m_board(board),
    m_player(player)
{
    m_attack = new Attack(this);

    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &AiBrain::timeout);
}

void AiBrain::start()
{
    //qDebug() << "AI from player" << m_player->id() << "start";
    qsrand(qrand());
    m_timer->setInterval(qrand() % ((3000 + 1) - 2000) + 2000);
    qDebug() << "Next AI turn in" << m_timer->interval();
    m_timer->start();
}

void AiBrain::stop()
{
    //qDebug() << "AI from player" << m_player->id() << "stop";
    m_timer->stop();
}

void AiBrain::calculateAttack()
{
    m_attack->reset();

    QList<Monster *> myMonsters = m_board->myMonsters(m_player);
    QList<Monster *> enemyMonsters = m_board->enemyMonsters(m_player);
    QList<Monster *> freeMonsters = m_board->freeMonsters();

    QList<VirtualAttack> possibleAttacks;

    // check all possible attacks
    foreach (Monster *myMonster, myMonsters) {
        foreach (Monster *enemyMonster, enemyMonsters) {
            possibleAttacks.append(VirtualAttack(myMonster, enemyMonster));
        }
        foreach (Monster *freeMonster, freeMonsters) {
            possibleAttacks.append(VirtualAttack(myMonster, freeMonster));
        }
    }
    qDebug() << "AI player" << m_player->id() << "has" << possibleAttacks.count() << "attack possibilitys";

    if (possibleAttacks.isEmpty())
        return;

    // TODO: calculate heuristics and select best turn
    m_attack->beginnAttack(possibleAttacks.first().sourceMonster()->id());
    m_attack->endAttack(possibleAttacks.first().destinationMonster()->id());

    emit startAttack(m_attack);
}

int AiBrain::calculateIntervall()
{
    qsrand(qrand());
    int reactionValue = (8 - m_player->reaction()) * 500;
    int min = 2000 + reactionValue;
    int max = 6000 + reactionValue;
    return qrand() % ((max + 1) - min) + min;
}

void AiBrain::timeout()
{
    calculateAttack();
    m_timer->setInterval(calculateIntervall());
    //qDebug() << "Next AI turn in" << m_timer->interval();
}

VirtualAttack::VirtualAttack(Monster *sourceMonster, Monster *destinationMonster) :
    m_sourceMonsters(sourceMonster),
    m_destinationMonster(destinationMonster)
{
    m_distance = distanceBetweenMonsters(m_sourceMonsters, m_destinationMonster);
}

Monster *VirtualAttack::sourceMonster()
{
    return m_sourceMonsters;
}

Monster *VirtualAttack::destinationMonster()
{
    return m_destinationMonster;
}

double VirtualAttack::percentage()
{
    return 0;
}

double VirtualAttack::distance()
{
    return m_distance;
}

double VirtualAttack::distanceBetweenMonsters(Monster *a, Monster *b)
{
    double dx = a->position().x() - b->position().x();
    double dy = a->position().y() - b->position().y();
    return sqrt(pow(dx,2) + pow(dy,2));
}
