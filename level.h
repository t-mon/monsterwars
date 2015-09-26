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

#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QDebug>

class Monster;
class Player;

class Level: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int levelId READ levelId NOTIFY levelIdChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString bestTime READ bestTime NOTIFY bestTimeChanged)
    Q_PROPERTY(bool unlocked READ unlocked NOTIFY unlockedChanged)

public:
    explicit Level(QObject *parent = 0);
    ~Level();

    void setName(const QString &name);
    QString name() const;

    void setLevelId(const int &levelId);
    int levelId() const;

    void setBestTime(const QString &bestTime);
    QString bestTime() const;

    void setTimeStamp(const int &timeStamp);
    int timeStamp() const;

    void setUnlocked(const bool &unlocked);
    bool unlocked() const;

    void setMonstersVariants(const QVariantList &monstersVariant);
    QVariantList monstersVariant() const;

    void setPlayersVariants(const QVariantList &playersVariant);
    QVariantList playersVariant() const;

private:
    QVariantList m_monstersVariant;
    QVariantList m_playersVariant;
    QString m_name;
    int m_levelId;
    int m_timeStamp;
    QString m_bestTime;
    bool m_unlocked;

signals:
    void levelIdChanged();
    void nameChanged();
    void bestTimeChanged();
    void unlockedChanged();

};

#endif // LEVEL_H
