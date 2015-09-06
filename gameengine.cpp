#include <QCoreApplication>
#include <QFileInfo>
#include <QJsonDocument>

#include "gameengine.h"
#include "board.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "attack.h"

GameEngine::GameEngine(QObject *parent):
    QObject(parent),
    m_timer(new QTimer(this)),
    m_board(new Board(this)),
    m_ticksPerSecond(25),
    m_running(false)
{    
    // Initialize boardsize
    m_rows = 40;
    m_columns = 70;

    // Initialize propertys
    m_strengthStepWidth = 0.05;
    m_reproductionStepWidth = 50;
    m_defenseStepWidth = 0.05;
    m_speedStepWidth = 0.08;

    m_pillowsModel = new AttackPillowModel(this);

    m_tickInterval = 1000 / m_ticksPerSecond;
    connect(this, &GameEngine::gameFinished, this, &GameEngine::onGameFinished);
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

QQmlListProperty<Level> GameEngine::levels()
{
    return QQmlListProperty<Level>(this, m_levels);
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
    m_dataDir = dataDir;
    emit dataDirChanged();
    initGameEngine();
}

void GameEngine::start()
{
    m_timer->start();
}

void GameEngine::stop()
{
    m_timer->stop();
}

int GameEngine::rows() const
{
    return m_rows;
}

int GameEngine::columns() const
{
    return m_columns;
}

bool GameEngine::running() const
{
    return m_running;
}

void GameEngine::startAttack(Attack *attack)
{
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

        AttackPillow *pillow = new AttackPillow(sourceMonster->player(),
                                                sourceMonster,
                                                destinationMonster,
                                                sourceMonster->split(),
                                                attackStrength,
                                                attackSpeed,
                                                this);

        qDebug() << "created pillow" << pillow->id() << sourceMonster->id() << " -> " << destinationMonster->id();
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
    qDebug() << "Attack" << pillow->sourceMonster()->id() << "  ->  " << pillow->destinationMonster()->id() << "finished";

    pillow->destinationMonster()->impact(pillow);
    m_pillowsModel->removePillow(pillow);
    emit pillowsChanged();

    pillow->deleteLater();
}

void GameEngine::stopGame()
{
    stop();
    qDebug() << "Game: stop";
    m_board->resetBoard();
}

void GameEngine::pauseGame()
{
    stop();
    qDebug() << "Game: pause";
}

void GameEngine::continueGame()
{
    qDebug() << "Game: continue";
    start();
}

void GameEngine::startGame(const int &levelId)
{
    Level *level = m_levelHash.value(levelId);
    m_board->setLevel(level);
    qDebug() << "Game: start Level" << levelId;
    start();
    calculateScores();
}

void GameEngine::loadLevels()
{
    QDir dir(QDir::currentPath() + m_dataDir.path());
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
        m_levels.append(level);
        m_levelHash.insert(level->levelId(), level);
        emit levelsChanged();
    }
}

void GameEngine::calculateScores()
{
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
        player->setPercentage((double)((int)(percentage * 100 + 0.5) / 100.0));
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
    connect(m_timer, &QTimer::timeout, this, &GameEngine::tick);

    connect(m_board, &Board::startAttack, this, &GameEngine::startAttack);
}

void GameEngine::slotTick()
{
    calculateScores();
}

void GameEngine::onGameFinished(const int &winnerId)
{
    if( winnerId == 1) {
        qDebug() << "GAME OVER!! You are the WINNER!!!";
    } else {
        qDebug() << "GAME OVER!! You have LOST the game!!!";
    }
    stop();
}
