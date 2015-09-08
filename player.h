#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>
#include <QColor>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pointCount READ pointCount NOTIFY pointCountChanged)
    Q_PROPERTY(double percentage READ percentage NOTIFY percentageChanged)
    Q_PROPERTY(QString colorString READ colorString() CONSTANT)

public:
    enum PlayerType {
        PlayerTypeHuman,
        PlayerTypeAi,
        PlayerTypeNone
    };

    explicit Player(int playerId, QObject *parent = 0);
    int id() const;

    void setColorString(const QString &colorString);
    QString colorString() const;

    void setPlayerType(const PlayerType &playerType);
    void setPlayerType(const QString &playerTypeString);
    PlayerType playerType() const;
    QString playerTypeString();

    // [0 - 8]
    void setStrength(const int &strength);
    int strength() const;

    // [0 - 8]
    void setSpeed(const int &speed);
    int speed() const;

    // [0 - 8]
    void setDefence(const int &defense);
    int defense() const;

    // [0 - 8]
    void setReproduction(const int &reproduction);
    int reproduction() const;

    // [0 - 8]
    void setReaction(const int &reaction);
    int reaction() const;

    double percentage() const;
    void setPercentage(const double &percentage);

    void setPointCount(const int &pointCount);
    int pointCount();
    void addPoints(int points);

private:
    int m_id;
    int m_pointCount;
    double m_percentage;
    QString m_colorString;
    PlayerType m_playerType;
    QString m_playerTypeString;
    int m_strength;
    int m_speed;
    int m_defense;
    int m_reproduction;
    int m_reaction;

    QString playerTypeToString(PlayerType playerType);

signals:
    void pointCountChanged();
    void percentageChanged();
};
#endif // PLAYER_H
