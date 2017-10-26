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

#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include <QObject>
#include <QSettings>

class PlayerSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool changed READ changed NOTIFY settingsChanged)
    Q_PROPERTY(int tunePoints READ tunePoints WRITE setTunePoints NOTIFY tunePointsChanged)
    Q_PROPERTY(int strengthPoints READ strengthPoints WRITE setStrengthPoints NOTIFY strengthPointsChanged)
    Q_PROPERTY(int defensePoints READ defensePoints WRITE setDefensePoints NOTIFY defensePointsChanged)
    Q_PROPERTY(int reproductionPoints READ reproductionPoints WRITE setReproductionPoints NOTIFY reproductionPointsChanged)
    Q_PROPERTY(int speedPoints READ speedPoints WRITE setSpeedPoints NOTIFY speedPointsChanged)


public:
    explicit PlayerSettings(QObject *parent = 0);

    bool muted() const;
    void setMuted(const bool &muted);

    bool changed() const;

    int tunePoints() const;
    void setTunePoints(const int &tunePoints);
    void increaseTunePoints();

    int strengthPoints() const;
    void setStrengthPoints(const int &strengthPoints);
    Q_INVOKABLE void increaseStrengthPoints();

    int defensePoints() const;
    void setDefensePoints(const int &defensePoints);
    Q_INVOKABLE void increaseDefensePoints();

    int reproductionPoints() const;
    void setReproductionPoints(const int &reproductionPoints);
    Q_INVOKABLE void increaseReproductionPoints();

    int speedPoints() const;
    void setSpeedPoints(const int &speedPoints);
    Q_INVOKABLE void increaseSpeedPoints();

    void resetSettings();

    Q_INVOKABLE void store();
    Q_INVOKABLE void restore();

private:
    bool m_muted;
    bool m_changed;

    int m_tunePoints;

    int m_strengthPoints;
    int m_defensePoints;
    int m_reproductionPoints;
    int m_speedPoints;

    // private members for restore option
    int m_tunePointsStored;
    int m_strengthPointsStored;
    int m_defensePointsStored;
    int m_reproductionPointsStored;
    int m_speedPointsStored;

signals:
    void mutedChanged();
    void tunePointsChanged();
    void strengthPointsChanged();
    void defensePointsChanged();
    void reproductionPointsChanged();
    void speedPointsChanged();

    void settingsStored();
    void settingsChanged();

};

#endif // PLAYERSETTINGS_H
