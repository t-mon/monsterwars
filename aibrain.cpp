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

    // check all possible attacks
    foreach (Monster *myMonster, myMonsters) {
        foreach (Monster *enemyMonster, enemyMonsters) {
            possibleAttacks.append(new VirtualAttack(myMonster, enemyMonster));
        }
        foreach (Monster *freeMonster, freeMonsters) {
            possibleAttacks.append(new VirtualAttack(myMonster, freeMonster));
        }
    }
    qDebug() << "AI player" << m_player->id() << "has" << possibleAttacks.count() << "attack possibilitys";

    if (possibleAttacks.isEmpty())
        return;

    // get the best attack of each heuristic



    // get shortest distance attack
    qSort(possibleAttacks.begin(), possibleAttacks.end(), compareDistance);
    VirtualAttack *shortestDistanceAttack = possibleAttacks.first();

    // get heighest attack
    qSort(possibleAttacks.begin(), possibleAttacks.end(), compareSourceValue);
    VirtualAttack *highestSourceAttack = possibleAttacks.first();

    // weakest enemy attack
    qSort(possibleAttacks.begin(), possibleAttacks.end(), compareDestinationValue);
    VirtualAttack *weakestTargetAttack = possibleAttacks.first();


    // create attack
    m_attack->reset();
    m_attack->beginnAttack(weakestTargetAttack->sourceMonster()->id());
    m_attack->endAttack(weakestTargetAttack->destinationMonster()->id());

    // perform attack
    emit startAttack(m_attack);

    qDeleteAll(possibleAttacks);
}

int AiBrain::calculateIntervall()
{
    qsrand(qrand());
    int reactionValue = (8 - m_player->reaction()) * 500;
    int min = 4000 + reactionValue;
    int max = 10000 + reactionValue;
    return qrand() % ((max + 1) - min) + min;
}

void AiBrain::timeout()
{
    calculateAttack();
    m_timer->setInterval(calculateIntervall());
    qDebug() << "Next AI turn in" << m_timer->interval();
}

VirtualAttack::VirtualAttack(Monster *sourceMonster, Monster *destinationMonster) :
    m_sourceMonsters(sourceMonster),
    m_destinationMonster(destinationMonster)
{
    m_distance = calculateDistance(m_sourceMonsters, m_destinationMonster);
}

Monster *VirtualAttack::sourceMonster()
{
    return m_sourceMonsters;
}

Monster *VirtualAttack::destinationMonster()
{
    return m_destinationMonster;
}

int VirtualAttack::points()
{
    return m_points;
}

double VirtualAttack::distance()
{
    return m_distance;
}

double VirtualAttack::calculateDistance(Monster *a, Monster *b)
{
    double dx = a->position().x() - b->position().x();
    double dy = a->position().y() - b->position().y();
    return sqrt(pow(dx,2) + pow(dy,2));
}

int VirtualAttack::calculatePoints()
{
//    int attackPoints = qRound(m_sourceMonsters->value() / 2);

//    double strengthMultiplicator = 1 + (sourceMonster()->player()->strength() * m_engine->strengthStepWidth());
//    double defenseMultiplicator = 1;

//    // check if this is a defense monster
//    if (destinationMonster()->monsterType() == Monster::MonsterTypeDefense) {
//        defenseMultiplicator -= 4 * m_engine->defenseStepWidth();
//    }
//    defenseMultiplicator -= (destinationMonster()->player()->defense() * m_engine->defenseStepWidth());

//    // take care of attack bonus
//    int attackValue = attackPoints * strengthMultiplicator;
//    int attackDifference = attackValue - attackPoints;

//    // take care of defense bonus
//    int defenseValue = attackPoints * defenseMultiplicator;
//    int defenseDifference = defenseValue - attackPoints;

//    int finalAttackValue = attackPoints - (abs(attackDifference + defenseDifference));

//    m_value -= finalAttackValue;
//    if(m_value < 0) {
//        setPlayer(attackPillow->player());
//        emit playerChanged();
//        m_value = abs(m_value);
//    }

}

bool compareDistance(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->distance() < attack2->distance();
}

bool compareSourceValue(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->sourceMonster()->value() > attack2->sourceMonster()->value();
}

bool compareDestinationValue(VirtualAttack *attack1, VirtualAttack *attack2)
{
    return attack1->destinationMonster()->value() < attack2->destinationMonster()->value();
}
