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

    void startAttack(Attack *attack);

    int ticksPerSecond() const;
    int tickInterval() const;

    double strengthStepWidth() const;
    double reproductionStepWidth() const;
    double defenseStepWidth() const;
    double speedStepWidth() const;

    Q_INVOKABLE void startGame(const int &levelId);
    Q_INVOKABLE void stopGame();
    Q_INVOKABLE void pauseGame();
    Q_INVOKABLE void continueGame();

    Q_INVOKABLE void attackFinished(QString pillowId);

private:
    QTimer *m_timer;
    QTimer *m_displayTimer;
    QElapsedTimer m_gameTimer;

    qint32 m_totalGameTimeMs;

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
    void gameFinished(const int &winnerId);

private slots:
    void initGameEngine();
    void slotTick();
    void onDisplayTimerTimeout();
    void onGameOver(const int &winnerId);

};
#endif // GAMEENGINE_H
