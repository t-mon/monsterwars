/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Monster Wars.                                     *
 *                                                                         *
 *  Monster Wars is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Monster Wars is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Monster Wars. If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "player.h"

Player::Player(int playerId, QObject *parent):
     QObject(parent),
     m_id(playerId)
{
    m_colorString = "white";
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

void Player::setColorString(const QString &colorString)
{
    m_colorString = colorString;
}

QString Player::colorString() const
{
    return m_colorString;
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

void Player::setReproduction(const int &reaction)
{
    m_reproduction = reaction;
}

int Player::reproduction() const
{
    return m_reproduction;
}

void Player::setReaction(const int &reaction)
{
    m_reaction = reaction;
}

int Player::reaction() const
{
    return m_reaction;
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
        return "PlayerTypeHuman";
        break;
    case PlayerTypeAi:
        return "PlayerTypeAi";
        break;
    default:
        qWarning() << "ERROR: unknown PlayerType!";
        return QString();
    }
}
