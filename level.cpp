#include "level.h"
#include "player.h"
#include "monster.h"

Level::Level(QObject *parent):
    QObject(parent)
{
}

Level::~Level()
{
}

void Level::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

QString Level::name() const
{
    return m_name;
}

void Level::setLevelId(const int &levelId)
{
    m_levelId = levelId;
    emit levelIdChanged();
}

int Level::levelId() const
{
    return m_levelId;
}

void Level::setMonstersVariants(const QVariantList &monstersVariant)
{
    m_monstersVariant = monstersVariant;
}

QVariantList Level::monstersVariant() const
{
    return m_monstersVariant;
}

void Level::setPlayersVariants(const QVariantList &playersVariant)
{
    m_playersVariant = playersVariant;
}

QVariantList Level::playersVariant() const
{
    return m_playersVariant;
}

