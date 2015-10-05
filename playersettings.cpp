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

#include "playersettings.h"

#include <QDebug>

PlayerSettings::PlayerSettings(QObject *parent) :
    QObject(parent)
{
    QSettings settings;
    settings.beginGroup("game");

    m_muted = settings.value("muted", false).toBool();
    emit mutedChanged();

    settings.endGroup();

    settings.beginGroup("player");
    m_tunePoints = settings.value("tunePoints", 0).toInt();
    m_tunePointsStored = m_tunePoints;
    emit tunePointsChanged();

    m_strengthPoints = settings.value("strength", 0).toInt();
    m_strengthPointsStored = m_strengthPoints;
    emit strengthPointsChanged();

    m_defensePoints = settings.value("defense", 0).toInt();
    m_defensePointsStored = m_defensePoints;
    emit defensePointsChanged();

    m_reproductionPoints = settings.value("reproduction", 0).toInt();
    m_reproductionPointsStored = m_reproductionPoints;
    emit reproductionPointsChanged();

    m_speedPoints = settings.value("speed", 0).toInt();
    m_speedPointsStored = m_speedPoints;
    emit speedPointsChanged();

    settings.endGroup();

    m_changed = false;
    emit settingsChanged();
}

bool PlayerSettings::muted() const
{
    return m_muted;
}

void PlayerSettings::setMuted(const bool &muted)
{
    m_muted = muted;
    emit mutedChanged();

    QSettings settings;
    settings.beginGroup("game");
    settings.setValue("muted", muted);
    settings.endGroup();
}

bool PlayerSettings::changed() const
{
    return m_changed;
}

int PlayerSettings::tunePoints() const
{
    return m_tunePoints;
}

void PlayerSettings::setTunePoints(const int &tunePoints)
{
    m_tunePoints = tunePoints;
    emit tunePointsChanged();

    qDebug() << "Player 1 -> tune points" << m_tunePoints;

    QSettings settings;
    settings.beginGroup("player");
    settings.setValue("tunePoints", m_tunePoints);
    settings.endGroup();
}

void PlayerSettings::increaseTunePoints()
{
    setTunePoints(m_tunePoints + 1);
    store();
}

int PlayerSettings::strengthPoints() const
{
    return m_strengthPoints;
}

void PlayerSettings::setStrengthPoints(const int &strengthPoints)
{
    m_strengthPoints = strengthPoints;
    emit strengthPointsChanged();

    qDebug() << "Player 1 -> strength" << m_strengthPoints;

    QSettings settings;
    settings.beginGroup("player");
    settings.setValue("strength", m_strengthPoints);
    settings.endGroup();

    m_changed = true;
    emit settingsChanged();
}

void PlayerSettings::increaseStrengthPoints()
{
    if (m_tunePoints > 0 && m_strengthPoints < 8) {
        setTunePoints(m_tunePoints - 1);
        setStrengthPoints(m_strengthPoints + 1);
    }
}

int PlayerSettings::defensePoints() const
{
    return m_defensePoints;
}

void PlayerSettings::setDefensePoints(const int &defensePoints)
{
    m_defensePoints = defensePoints;
    emit defensePointsChanged();

    qDebug() << "Player 1 -> defense" << m_defensePoints;

    QSettings settings;
    settings.beginGroup("player");
    settings.setValue("defense", m_defensePoints);
    settings.endGroup();

    m_changed = true;
    emit settingsChanged();
}

void PlayerSettings::increaseDefensePoints()
{
    if (m_tunePoints > 0 && m_defensePoints < 8) {
        setTunePoints(m_tunePoints - 1);
        setDefensePoints(m_defensePoints + 1);
    }
}

int PlayerSettings::reproductionPoints() const
{
    return m_reproductionPoints;
}

void PlayerSettings::setReproductionPoints(const int &reproductionPoints)
{
    m_reproductionPoints = reproductionPoints;
    emit reproductionPointsChanged();

    qDebug() << "Player 1 -> reproduction" << m_reproductionPoints;

    QSettings settings;
    settings.beginGroup("player");
    settings.setValue("reproduction", m_reproductionPoints);
    settings.endGroup();

    m_changed = true;
    emit settingsChanged();
}

void PlayerSettings::increaseReproductionPoints()
{
    if (m_tunePoints > 0 && m_reproductionPoints < 8) {
        setTunePoints(m_tunePoints - 1);
        setReproductionPoints(m_reproductionPoints + 1);
    }
}

int PlayerSettings::speedPoints() const
{
    return m_speedPoints;
}

void PlayerSettings::setSpeedPoints(const int &speedPoints)
{
    m_speedPoints = speedPoints;
    emit speedPointsChanged();

    qDebug() << "Player 1 -> speed" << m_speedPoints;

    QSettings settings;
    settings.beginGroup("player");
    settings.setValue("speed", m_speedPoints);
    settings.endGroup();

    m_changed = true;
    emit settingsChanged();
}

void PlayerSettings::increaseSpeedPoints()
{
    if (m_tunePoints > 0 && m_speedPoints < 8) {
        setTunePoints(m_tunePoints - 1);
        setSpeedPoints(m_speedPoints + 1);
    }
}

void PlayerSettings::resetSettings()
{
    qDebug() << "Reset player settings...";
    setTunePoints(0);
    setSpeedPoints(0);
    setStrengthPoints(0);
    setDefensePoints(0);
    setReproductionPoints(0);
    store();
}

void PlayerSettings::store()
{
    qDebug() << "Store settings...";
    m_tunePointsStored = m_tunePoints;
    m_strengthPointsStored = m_strengthPoints;
    m_defensePointsStored = m_defensePoints;
    m_reproductionPointsStored = m_reproductionPoints;
    m_speedPointsStored = m_speedPoints;

    emit settingsStored();

    m_changed = false;
    emit settingsChanged();
}

void PlayerSettings::restore()
{
    qDebug() << "Restore settings...";
    setTunePoints(m_tunePointsStored);

    setStrengthPoints(m_strengthPointsStored);
    setDefensePoints(m_defensePointsStored);
    setReproductionPoints(m_reproductionPointsStored);
    setSpeedPoints(m_speedPointsStored);

    m_changed = false;
    emit settingsChanged();
}
