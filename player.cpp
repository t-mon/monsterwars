#include "player.h"


Player::Player(int playerId, QObject *parent):
    m_id(playerId), QObject(parent)
{
    m_color = QColor(255, 255, 255);
    m_playerType = PlayerTypeNone;
    m_playerTypeString = "None";
    m_strength = 0;
    m_speed = 0;
    m_defense = 0;
    m_reproduction = 0;
    m_percentage = 0;
    m_pointCount = 0;
}

int Player::id() const
{
    return m_id;
}

void Player::setColor(const QColor &color)
{
    m_color = color;
}

QColor Player::color() const
{
    return m_color;
}

void Player::setPlayerType(const Player::PlayerType &playerType)
{
    m_playerType = playerType;
    m_playerTypeString = playerTypeToString(playerType);
}

void Player::setPlayerType(const QString &playerType)
{
    if (playerType == "PlayerTypeHuman") {
        m_playerType = PlayerTypeHuman;
    } else if (playerType == "PlayerTypeAi") {
        m_playerType = PlayerTypeAi;
    } else {
        qWarning() << "ERROR: unknown PlayerType. Please Check the level.json file";
    }
    m_playerTypeString = playerTypeToString(m_playerType);
}

Player::PlayerType Player::playerType() const
{
    return m_playerType;
}

QString Player::playerTypeString()
{
    return m_playerTypeString;
}

void Player::setStrength(const int &strength)
{
    m_strength = strength;
}

int Player::strength() const
{
    return m_strength;
}

void Player::setSpeed(const int &speed)
{
    m_speed = speed;
}

int Player::speed() const
{
    return m_speed;
}

void Player::setDefence(const int &defense)
{
    m_defense = defense;
}

int Player::defense() const
{
    return m_defense;
}

void Player::setReproduction(const int &reproduction)
{
    m_reproduction = reproduction;
}

int Player::reproduction() const
{
    return m_reproduction;
}

double Player::percentage() const
{
    return m_percentage;
}

void Player::setPercentage(const double &percentage)
{
    m_percentage = percentage;
    emit percentageChanged();
}

void Player::setPointCount(const int &pointCount)
{
    m_pointCount = pointCount;
    emit pointCountChanged();
}

int Player::pointCount()
{
    return m_pointCount;
}

void Player::addPoints(int points)
{
    m_pointCount += points;
    emit pointCountChanged();
}

QString Player::playerTypeToString(Player::PlayerType playerType)
{
    switch (playerType) {
    case PlayerTypeHuman:
        return "Human";
        break;
    case PlayerTypeAi:
        return "AI";
        break;
    default:
        qWarning() << "ERROR: unknown PlayerType!";
        break;
    }
}
