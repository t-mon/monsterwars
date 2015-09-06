#include "attackpillow.h"
#include "player.h"
#include "monster.h"

AttackPillow::AttackPillow(Player *player, Monster *sourceMonster, Monster *destinationMonster, int count, int strength, int speed, QObject *parent):
    QObject(parent),
    m_id(QUuid::createUuid().toString()),
    m_player(player),
    m_sourceMonster(sourceMonster),
    m_destinationMonster(destinationMonster),
    m_count(count),
    m_strength(strength),
    m_speed(speed)
{
}

QString AttackPillow::id() const
{
    return m_id;
}

Player *AttackPillow::player() const
{
    return m_player;
}

Monster *AttackPillow::sourceMonster() const
{
    return m_sourceMonster;
}

Monster *AttackPillow::destinationMonster() const
{
    return m_destinationMonster;
}

int AttackPillow::count() const
{
    return m_count;
}

QString AttackPillow::colorString() const
{
    return m_player->colorString();
}

int AttackPillow::strength() const
{
    return m_strength;
}

int AttackPillow::speed() const
{
    return m_speed;
}

