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

#include <QCoreApplication>
#include <QFileInfo>
#include <QJsonDocument>
#include <QSettings>

#include "gameengine.h"
#include "board.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "attack.h"

GameEngine::GameEngine(QObject *parent):
    QObject(parent),
    m_timer(new QTimer(this)),
    m_displayTimer(new QTimer(this)),
    m_board(new Board(this)),
    m_ticksPerSecond(25),
    m_rows(40),
    m_columns(70),
    m_running(false),
    m_newHighScore(false),
    m_tunePointEarned(false)
{
    // Initialize propertys
    m_strengthStepWidth = 0.1;
    m_defenseStepWidth = 0.1;
    m_reproductionStepWidth = 50;
    m_speedStepWidth = 0.25;

    m_pillowsModel = new AttackPillowModel(this);
    m_levels = new LevelModel(this);

    m_playerSettings = new PlayerSettings(this);

    m_tickInterval = 1000 / m_ticksPerSecond;
    connect(this, &GameEngine::gameFinished, this, &GameEngine::onGameOver);
    connect(m_board, &Board::boardChanged, this, &GameEngine::boardChanged);
}

QHash<int, QVariantMap> GameEngine::levelDescriptions() const
{
    return m_levelDescriptions;
}

QVariantMap GameEngine::levelDescription(int levelId) const
{
    return m_levelDescriptions.value(levelId);
}

Board *GameEngine::board() const
{
    return m_board;
}

LevelModel *GameEngine::levels()
{
    return m_levels;
}

AttackPillowModel *GameEngine::pillows()
{
    return m_pillowsModel;
}

QUrl GameEngine::dataDir() const
{
    return m_dataDir;
}

void GameEngine::setDataDir(const QUrl &dataDir)
{
    qDebug() << "Game: set data directory" << dataDir.toString();
    m_dataDir = dataDir;
    emit dataDirChanged();
    initGameEngine();
}

void GameEngine::start()
{
    m_timer->start();
    m_displayTimer->start();
    m_running = true;
    emit runningChanged();
}

void GameEngine::stop()
{
    m_timer->stop();
    m_displayTimer->stop();
    m_running = false;
    emit runningChanged();
}

int GameEngine::rows() const
{
    return m_rows;
}

int GameEngine::columns() const
{
    return m_columns;
}

QString GameEngine::gameTime() const
{
    return QTime::fromMSecsSinceStartOfDay(m_totalGameTimeMs).toString("mm:ss.zzz");
}

QString GameEngine::displayGameTime() const
{
    return QTime::fromMSecsSinceStartOfDay(m_totalGameTimeMs).toString("mm:ss");
}

bool GameEngine::running() const
{
    return m_running;
}

bool GameEngine::newHighScore() const
{
    return m_newHighScore;
}

bool GameEngine::tunePointEarned() const
{
    return m_tunePointEarned;
}

int GameEngine::winnerId() const
{
    return m_winnerId;
}

void GameEngine::startAttack(Attack *attack)
{
    qDebug() << "Start attack -> " << attack->sourceIds() << "->" << attack->destinationId();

    foreach (int monsterId, attack->sourceIds()) {
        Monster* sourceMonster = board()->monster(monsterId);
        Monster* destinationMonster = board()->monster(attack->destinationId());

        // check attack strength
        int attackStrength = 0;
        if (sourceMonster->monsterType() == Monster::MonsterTypeStrength) {
            attackStrength += 4;
        }
        attackStrength += sourceMonster->player()->strength();

        // check attack speed
        int attackSpeed = 0;
        if (sourceMonster->monsterType() == Monster::MonsterTypeSpeed) {
            attackSpeed += 4;
        }
        attackSpeed += sourceMonster->player()->speed();

        // create pillow
        AttackPillow *pillow = new AttackPillow(sourceMonster->player(), sourceMonster, destinationMonster, sourceMonster->split(), attackStrength, attackSpeed, this);

        if (pillow->count() == 0) {
            pillow->deleteLater();
            continue;
        }

        m_pillowList.insert(pillow->id(), pillow);
        m_pillowsModel->addPillow(pillow);
    }
}

int GameEngine::ticksPerSecond() const
{
    return m_ticksPerSecond;
}

int GameEngine::tickInterval() const
{
    return m_tickInterval;
}

PlayerSettings *GameEngine::playerSettings()
{
    return m_playerSettings;
}

double GameEngine::strengthStepWidth() const
{
    return m_strengthStepWidth;
}

double GameEngine::reproductionStepWidth() const
{
    return m_reproductionStepWidth;
}

double GameEngine::defenseStepWidth() const
{
    return m_defenseStepWidth;
}

double GameEngine::speedStepWidth() const
{
    return m_speedStepWidth;
}

void GameEngine::attackFinished(QString pillowId)
{
    AttackPillow *pillow = m_pillowList.take(pillowId);
    qDebug() << "Attack" << pillow->sourceMonster()->id() << "->" << pillow->destinationMonster()->id() << "finished";

    pillow->destinationMonster()->impact(pillow);
    m_pillowsModel->removePillow(pillow);
    emit pillowsChanged();

    pillow->deleteLater();
}

void GameEngine::resetGameSettings()
{
    qDebug() << "Reset game settings...";
    m_levels->resetLevelSettings();
    m_playerSettings->resetSettings();
}

void GameEngine::startGame(const int &levelId)
{
    Level *level = m_levelHash.value(levelId);
    m_board->setLevel(level);

    foreach (Player *player, m_board->playersList()) {
        if (player->playerType() == Player::PlayerTypeAi) {
            AiBrain *brain = new AiBrain(m_board, player, m_strengthStepWidth, m_defenseStepWidth, this);
            qDebug() << "Create AI for player" << player->id();
            m_brains.insert(player, brain);
            connect(brain, &AiBrain::startAttack, this, &GameEngine::startAttack);
        }
    }

    qDebug() << "Game: start Level" << levelId;
    start();

    foreach (AiBrain *brain, m_brains.values()) {
        brain->start();
    }

    // reset engine properties
    m_gameOver = false;

    m_newHighScore = false;
    emit newHighScoreChanged();

    m_tunePointEarned = false;
    emit tunePointEarnedChanged();

    m_totalGameTimeMs = 0;

    m_gameTimer.restart();
    emit displayGameTimeChanged();

    calculateScores();
    emit gameStarted();
}

void GameEngine::restartGame()
{
    qDebug() << "Game: restart";
    int levelId = m_board->level()->levelId();
    stopGame();
    startGame(levelId);
    emit gameRestarted();
}

void GameEngine::stopGame()
{
    qDebug() << "Game: stop";
    stop();

    // clean up brains
    foreach (AiBrain *brain, m_brains.values()) {
        brain->deleteLater();
    }
    m_brains.clear();

    // stop game timer
    m_totalGameTimeMs += m_gameTimer.elapsed();
    emit gameTimeChanged();

    // clean up existing pillows
    m_pillowsModel->clearModel();
    foreach (AttackPillow *pillow, m_pillowList.values()) {
        pillow->deleteLater();
    }
    m_pillowList.clear();

    // reset the board
    m_board->resetBoard();

    if (!m_gameOver) {
        emit gameStoped();
    }
    m_gameOver = true;
}

void GameEngine::pauseGame()
{
    if (m_gameOver)
        return;

    // stop AIs
    foreach (AiBrain *brain, m_brains.values()) {
        brain->stop();
    }

    // stop GameEngine
    stop();

    // stop game timer
    m_totalGameTimeMs += m_gameTimer.elapsed();
    emit gameTimeChanged();

    qDebug() << "Game: pause" << m_totalGameTimeMs;
    emit gamePaused();
}

void GameEngine::continueGame()
{
    // if game over...ignore it
    if (m_gameOver)
        return;

    // start AIs
    foreach (AiBrain *brain, m_brains.values()) {
        brain->start();
    }

    // start GameEngine
    start();

    // continue game timer
    m_gameTimer.restart();
    emit gameTimeChanged();

    qDebug() << "Game: continue";
    emit gameContinue();
}

void GameEngine::loadLevels()
{
    QString dirString = m_dataDir.toString();
    QDir dir;
    if (dirString.startsWith("file:/")) {
        dir.setPath(m_dataDir.path() + "/levels");
    } else {
        dir.setPath(m_dataDir.toString() + "/levels");
    }

    QStringList levelDirs = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs, QDir::Name);

    qDebug() << "searching level data in" << dir.path();

    foreach (const QString &levelDir, levelDirs) {
        if (!levelDir.startsWith("level")) {
            continue;
        }

        QFileInfo fi(dir.absolutePath() + "/" + levelDir + "/level.json");
        if (!fi.exists()) {
            qDebug() << "Level directory" << levelDir << "does not contain a level.json file.";
            continue;
        }

        QFile levelFile(fi.absoluteFilePath());
        if (!levelFile.open(QFile::ReadOnly)) {
            qDebug() << "Cannot open level file for reading:" << fi.absoluteFilePath();
            continue;
        }

        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(levelFile.readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            qDebug() << "Cannot parse level file:" << error.errorString();
            continue;
        }

        QVariantMap levelData = jsonDoc.toVariant().toMap();
        qDebug() << "   -> loading level" << levelData.value("id").toInt() << "...";
        Level *level = new Level(this);
        level->setName(levelData.value("name").toString());
        level->setLevelId(levelData.value("id").toInt());
        level->setPlayersVariants(levelData.value("players").toList());
        level->setMonstersVariants(levelData.value("monsters").toList());

        QSettings settings;
        settings.beginGroup(level->name());
        level->setTimeStamp(settings.value("timeStamp", 0).toInt());
        level->setUnlocked(settings.value("unlocked", false).toBool());
        settings.endGroup();

        if (level->levelId() == 1) {
            level->setUnlocked(true);
        }

        m_levels->addLevel(level);
        m_levelHash.insert(level->levelId(), level);
    }
    m_levels->sortLevels();
    emit levelsChanged();

    // now check if there are new levels and make sure the last level is unlocked
    foreach (Level *level, m_levels->levels()) {
        if (level->timeStamp() != 0) {
            // get next level
            Level *nextLevel = 0;
            nextLevel = m_levelHash.value(level->levelId() + 1);
            if (nextLevel) {
                QSettings settings;
                settings.beginGroup(nextLevel->name());
                settings.setValue("unlocked", true);
                settings.endGroup();
                if (!nextLevel->unlocked()) {
                    qDebug() << "   -> Unlock last level" << nextLevel->levelId();
                }
                nextLevel->setUnlocked(true);
            }
        }
    }
}

void GameEngine::calculateScores()
{
    if (!m_running)
        return;

    int total = 0;
    foreach (Player *player, m_board->playersList()) {
        player->setPointCount(0);
        foreach (Monster *monster, m_board->monstersList()) {
            if (monster->player()->id() == player->id()){
                player->addPoints(monster->value());
                total += monster->value();
            }
        }
        foreach (AttackPillow *pillow, m_pillowsModel->pillows()) {
            if (pillow->player()->id() == player->id()){
                player->addPoints(pillow->count());
                total += pillow->count();
            }
        }
    }
    foreach (Player *player, m_board->playersList()) {
        if (player->pointCount() == 0) {
            player->setPercentage(0);
        }
        double percentage = (double)player->pointCount() / total;
        player->setPercentage((double)(qRound(percentage * 100) / 100.0));
        if (percentage == 1) {
            emit gameFinished(player->id());
        }
    }
}

void GameEngine::initGameEngine()
{
    loadLevels();

    m_timer->setInterval(1000 / m_ticksPerSecond);
    m_timer->setTimerType(Qt::PreciseTimer);

    connect(m_timer, &QTimer::timeout, this, &GameEngine::slotTick);

    m_totalGameTimeMs = 0;
    emit displayGameTimeChanged();
    m_displayTimer->setInterval(200);
    connect(m_displayTimer, &QTimer::timeout, this, &GameEngine::onDisplayTimerTimeout);

    connect(m_board, &Board::startAttack, this, &GameEngine::startAttack);
}

void GameEngine::slotTick()
{
    m_board->tick();
    calculateScores();
}

void GameEngine::onDisplayTimerTimeout()
{
    m_totalGameTimeMs += m_gameTimer.elapsed();
    m_gameTimer.restart();
    emit displayGameTimeChanged();
}

void GameEngine::onGameOver(const int &winnerId)
{
    if (m_gameOver)
        return;

    if( winnerId == 1) {
        qDebug() << "Game Over!! You are the winner!";
    } else {
        qDebug() << "Game Over!! You lost the game. Player" << winnerId << "won the game.";
    }

    foreach (AiBrain *brain, m_brains.values()) {
        brain->stop();
    }

    stop();
    // stop game timer
    m_totalGameTimeMs += m_gameTimer.elapsed();
    m_finalTime = m_totalGameTimeMs;
    emit gameTimeChanged();
    emit displayGameTimeChanged();

    if (winnerId == 1) {
        if (m_board->level()->timeStamp() > m_finalTime || m_board->level()->timeStamp() == 0) {

            // check if we earned a tune point
            if (m_board->level()->timeStamp() == 0) {
                m_playerSettings->increaseTunePoints();
                qDebug() << "Tune points +1";
                m_tunePointEarned = true;
                emit tunePointEarnedChanged();
            }
            m_newHighScore = true;
            emit newHighScoreChanged();
            qDebug() << "New highscore!";
            m_board->level()->setTimeStamp(m_finalTime);
            QSettings settings;
            settings.beginGroup(m_board->level()->name());
            settings.setValue("timeStamp", m_finalTime);
            settings.setValue("unlocked", true);
            settings.endGroup();

            Level *nextLevel = 0;

            nextLevel = m_levelHash.value(m_board->level()->levelId() + 1);

            if (nextLevel) {
                settings.beginGroup(nextLevel->name());
                settings.setValue("unlocked", true);
                settings.endGroup();
                if (!nextLevel->unlocked()) {
                    qDebug() << "Unlock next level" << nextLevel->levelId();
                }
                nextLevel->setUnlocked(true);
            }
        } else {
            m_newHighScore = false;
            emit newHighScoreChanged();
        }
    }

    m_winnerId = winnerId;
    emit winnerIdChanged();

    m_gameOver = true;
    emit gameOver();
}
