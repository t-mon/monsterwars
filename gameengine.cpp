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
    m_ticksPerSecond(25)
{    
    // Initialize boardsize
    m_rows = 75;
    m_columns = 100;

    // Initialize propertys
    m_strengthStepWidth = 0.05;
    m_reproductionStepWidth = 50;
    m_defenseStepWidth = 0.05;
    m_speedStepWidth = 0.08;

    m_tickInterval = 1000 / m_ticksPerSecond;
    connect(this, &GameEngine::gameFinished, this, &GameEngine::onGameFinished);
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
    calculateScores();
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

void GameEngine::startAttack(Attack *attack)
{
    foreach (int monsterId, attack->sourceIds()) {
        Monster* sourceMonster = board()->level()->monster(monsterId);
        Monster* destinationMonster = board()->level()->monster(attack->destinationId());

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

        ParticleCloud *particleCloud = new ParticleCloud(sourceMonster->player(),
                                                         sourceMonster->split(),
                                                         attackStrength,
                                                         attackSpeed,
                                                         sourceMonster->position().x(),
                                                         sourceMonster->position().y(),
                                                         this);
        destinationMonster->impact(particleCloud);
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
        m_levelDescriptions.insert(levelData.value("id").toInt(), levelData);
    }
}

void GameEngine::calculateScores()
{
    int total = 0;
    Level* level = board()->level();
    foreach (Player* player, level->players()) {
        player->setPointCount(0);
        foreach (Monster *monster, level->monsteres()) {
            if (monster->player()->id() == player->id()){
                player->addPoints(monster->value());
                total += monster->value();
            }
        }
    }
    foreach (Player* player, level->players()) {
        if (player->pointCount() == 0) {
            player->setPercentage(0);
        }
        double percentage = (double)player->pointCount() / total;
        if (percentage == 1) {
            emit gameFinished(player->id());
        }

        player->setPercentage((double)((int)(percentage * 100 + 0.5) / 100.0));
    }
}


void GameEngine::initGameEngine()
{
    loadLevels();

    m_timer->setInterval(1000 / m_ticksPerSecond);
    m_timer->setTimerType(Qt::PreciseTimer);

    connect(m_timer, &QTimer::timeout, this, &GameEngine::slotTick);
    connect(m_timer, &QTimer::timeout, this, &GameEngine::tick);

    m_board->createBoard();
    m_board->setLevel(m_levelDescriptions.value(1));
    connect(m_board, &Board::startAttack, this, &GameEngine::startAttack);

    start();
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
    m_timer->stop();
}
