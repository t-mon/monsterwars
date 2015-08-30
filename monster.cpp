#include "monster.h"
#include "player.h"
#include "gameengine.h"
#include "board.h"
#include "level.h"
#include "node.h"

Monster::Monster(GameEngine *engine, Monster::MonsterType monsterType, int id, int startValue, QPoint position, QColor color, QObject *parent):
    QObject(parent),
    m_engine(engine),
    m_monsterType(monsterType),
    m_id(id),
    m_value(startValue),
    m_position(position),
    m_player(0),
    m_color(color)
{
    m_tickCounter = 0;
    select(false);
    connect(m_engine, &GameEngine::tick, this, &Monster::slotTick);
}

Monster::Monster(GameEngine *engine = 0, int startValue = 0):
    QObject(engine),
    m_engine(engine),
    m_monsterType(MonsterTypeNormal),
    m_id(-1),
    m_value(startValue),
    m_position(QPoint()),
    m_player(0),
    m_color(QColor(255, 255, 255))
{
    m_tickCounter = 0;
    select(false);
    connect(m_engine, &GameEngine::tick, this, &Monster::slotTick);
}

void Monster::setMonsterType(const Monster::MonsterType &monsterType)
{
    m_monsterType = monsterType;
    m_monsterTypeString = monsterTypeToString(monsterType);
}

bool Monster::setMonsterType(const QString &monsterType)
{
    if (monsterType == "MonsterTypeNormal") {
        m_monsterType =MonsterTypeNormal;
    } else if (monsterType == "MonsterTypeStrength") {
        m_monsterType = MonsterTypeStrength;
    } else if (monsterType == "MonsterTypeSpeed") {
        m_monsterType = MonsterTypeSpeed;
    } else if (monsterType == "MonsterTypeReproduction") {
        m_monsterType = MonsterTypeReproduction;
    } else if (monsterType == "MonsterTypeDefense") {
        m_monsterType = MonsterTypeDefense;
    } else {
        qWarning() << "ERROR: unknown MonsterType!" << monsterType;
        return false;
    }
    m_monsterTypeString = monsterTypeToString(m_monsterType);
    return true;
}

Monster::MonsterType Monster::monsterType() const
{
    return m_monsterType;
}

QString Monster::monsterTypeString() const
{
    return m_monsterTypeString;
}

void Monster::setPlayer(Player *player)
{
    m_player = player;
    m_color = m_player->color();
    emit playerChanged();
    emit colorChanged();
}

Player *Monster::player() const
{
    return m_player;
}

void Monster::setId(const int &id)
{
    m_id = id;
}

int Monster::id() const
{
    return m_id;
}

int Monster::value() const
{
    return m_value;
}

int Monster::size() const
{
    return m_size;
}

void Monster::setSize(const int &size)
{
    m_size = size;
    m_maxValue = 120 + size * 10;
}

void Monster::setPosition(const QPoint &position)
{
    m_position = position;
}

QPoint Monster::position() const
{
    return m_position;
}

void Monster::setColor(const QColor &color)
{
    m_color = color;
}

QColor Monster::color() const
{
    return m_color;
}

void Monster::setColorString(const QString &colorString)
{

}

void Monster::select(const bool &selected)
{
    m_selected = selected;
    emit selectedChanged();
}

bool Monster::selected() const
{
    return m_selected;
}

int Monster::split()
{
    m_value = m_value / 2;
    emit valueChanged();
    return m_value;
}

void Monster::impact(ParticleCloud *particleCloud)
{
    // if its a free monster
    if (player()->id() == 0) {
        setPlayer(particleCloud->player());
        m_value += particleCloud->count();
        emit playerChanged();
    } else if (particleCloud->color() == m_color) {
        m_value += particleCloud->count();
    } else {
        // Seems to be a confrontation!
        double strengthMultiplicator = 1 + (particleCloud->strength() * m_engine->strengthStepWidth());
        double defenseMultiplicator = 1;

        // check if this is a defense monster
        if (monsterType() == MonsterTypeDefense) {
            defenseMultiplicator -= 4 * m_engine->defenseStepWidth();
        }
        defenseMultiplicator -= (player()->defense() * m_engine->defenseStepWidth());

        // take care of attack bonus
        int attackValue = particleCloud->count() * strengthMultiplicator;
        int attackDifference = attackValue - particleCloud->count();

        // take care of defense bonus
        int defenseValue = particleCloud->count() * defenseMultiplicator;
        int defenseDifference = defenseValue - particleCloud->count();

        int finalAttackValue = particleCloud->count() - (abs(attackDifference + defenseDifference));

        m_value -= finalAttackValue;
        if(m_value < 0) {
            setPlayer(particleCloud->player());
            emit playerChanged();
            m_value = abs(m_value);
        }
        // if value is 0 this board has no longer a player -> neutral
        if (m_value == 0) {
            setPlayer(m_engine->board()->level()->player(0));
        }
    }
    particleCloud->deleteLater();
    emit impact();
    emit valueChanged();
}

QString Monster::monsterTypeToString(Monster::MonsterType monsterType)
{
    switch (monsterType) {
    case Monster::MonsterTypeNormal:
        return "Normal";
        break;
    case Monster::MonsterTypeDefense:
        return "Defense";
        break;
    case Monster::MonsterTypeReproduction:
        return "Reproduction";
        break;
    case Monster::MonsterTypeSpeed:
        return "Speed";
        break;
    case Monster::MonsterTypeStrength:
        return "Strength";
        break;
    default:
        qWarning() << "ERROR: unknown MonsterType!";
        break;
    }
}

void Monster::slotTick()
{
    // stop counting if monster is empty
    if (m_value == 0){
        return;
    }
    //  stop counting if maxValue is reached
    if (m_value >= m_maxValue){
        return;
    }
    m_tickCounter++;
    int intervall = 1000 - ((player()->reproduction()) * m_engine->tickInterval());

    if (monsterType() == MonsterTypeReproduction) {
        intervall -= 6 * m_engine->tickInterval();
    }

    if (m_tickCounter * m_engine->tickInterval() == intervall) {
        m_value += 1;
        m_tickCounter = 0;
        emit valueChanged();
    }
}

