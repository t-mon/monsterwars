#include "particlecloud.h"
#include "player.h"

ParticleCloud::ParticleCloud(Player *player, int count, int strength, int speed, int x, int y, QObject *parent):
    QObject(parent),
    m_player(player),
    m_count(count),
    m_strength(strength),
    m_speed(speed),
    m_x(x),
    m_y(y)
{
}

Player *ParticleCloud::player() const
{
    return m_player;
}

int ParticleCloud::count() const
{
    return m_count;
}

QColor ParticleCloud::color() const
{
    return m_player->color();
}

int ParticleCloud::strength() const
{
    return m_strength;
}

int ParticleCloud::speed() const
{
    return m_speed;
}

int ParticleCloud::x()
{
    return m_x;
}

int ParticleCloud::y()
{
    return m_y;
}
