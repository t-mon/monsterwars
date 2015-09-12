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

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QTime>
#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QQmlListProperty>
#include <QUuid>

#include "attackpillowmodel.h"
#include "aibrain.h"

class Level;
class Player;
class Monster;
class Board;
class Attack;
class AttackPillow;

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl dataDir READ dataDir WRITE setDataDir NOTIFY dataDirChanged)
    Q_PROPERTY(Board *board READ board NOTIFY boardChanged)
    Q_PROPERTY(QString displayGameTime READ displayGameTime NOTIFY displayGameTimeChanged)
    Q_PROPERTY(QString gameTime READ gameTime NOTIFY gameTimeChanged)
    Q_PROPERTY(int winnerId READ winnerId NOTIFY winnerIdChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(QQmlListProperty<Level> levels READ levels NOTIFY levelsChanged)
    Q_PROPERTY(AttackPillowModel *pillows READ pillows NOTIFY pillowsChanged)

public:
    explicit GameEngine(QObject *parent = 0);

    QHash<int, QVariantMap> levelDescriptions() const;
    QVariantMap levelDescription(int levelId) const;
    Board* board() const;

    QQmlListProperty<Level> levels();
    AttackPillowModel *pillows();

    QUrl dataDir() const;
    void setDataDir(const QUrl &dataDir);

    void start();
    void stop();

    int rows() const;
    int columns() const;

    QString gameTime() const;
    QString displayGameTime() const;

    bool running() const;

    int winnerId() const;

    void startAttack(Attack *attack);

    int ticksPerSecond() const;
    int tickInterval() const;

    Q_INVOKABLE double strengthStepWidth() const;
    Q_INVOKABLE double reproductionStepWidth() const;
    Q_INVOKABLE double defenseStepWidth() const;
    Q_INVOKABLE double speedStepWidth() const;

    Q_INVOKABLE void startGame(const int &levelId);
    Q_INVOKABLE void restartGame();
    Q_INVOKABLE void stopGame();
    Q_INVOKABLE void pauseGame();
    Q_INVOKABLE void continueGame();

    Q_INVOKABLE void attackFinished(QString pillowId);

private:
    QTimer *m_timer;
    QTimer *m_displayTimer;
    QElapsedTimer m_gameTimer;

    qint32 m_totalGameTimeMs;
    qint32 m_finalTime;
    bool m_gameOver;

    QUrl m_dataDir;
    QHash<int, QVariantMap> m_levelDescriptions;
    QList<Level *> m_levels;
    AttackPillowModel *m_pillowsModel;
    QHash<QString, AttackPillow *> m_pillowList;

    QHash<Player *, AiBrain *> m_brains;
    QHash<int, Level *> m_levelHash;

    Board *m_board;
    int m_ticksPerSecond;
    int m_tickInterval;
    int m_rows;
    int m_columns;
    int m_winnerId;
    bool m_running;

    double m_strengthStepWidth;
    double m_reproductionStepWidth;
    double m_defenseStepWidth;
    double m_speedStepWidth;

    void loadLevels();
    void loadPlayerSettings();
    void calculateScores();

signals:
    void tick();
    void dataDirChanged();
    void boardChanged();
    void levelsChanged();
    void pillowsChanged();
    void runningChanged();
    void gameTimeChanged();
    void displayGameTimeChanged();
    void gameOver();
    void gameFinished(const int &winnerId);
    void winnerIdChanged();

private slots:
    void initGameEngine();
    void slotTick();
    void onDisplayTimerTimeout();
    void onGameOver(const int &winnerId);

};
#endif // GAMEENGINE_H
