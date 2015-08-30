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
    Q_PROPERTY(QColor color READ color() CONSTANT)

public:
    enum PlayerType {
        PlayerTypeHuman,
        PlayerTypeAi,
        PlayerTypeNone
    };

    explicit Player(int playerId, QObject *parent = 0);
    int id() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setPlayerType(const PlayerType &playerType);
    void setPlayerType(const QString &playerTypeString);
    PlayerType playerType() const;
    QString playerTypeString();

    void setStrength(const int &strength);
    int strength() const;

    void setSpeed(const int &speed);
    int speed() const;

    void setDefence(const int &defense);
    int defense() const;

    void setReproduction(const int &reproduction);
    int reproduction() const;

    double percentage() const;
    void setPercentage(const double &percentage);

    void setPointCount(const int &pointCount);
    int pointCount();
    void addPoints(int points);

private:
    int m_id;
    int m_pointCount;
    double m_percentage;
    QColor m_color;
    PlayerType m_playerType;
    QString m_playerTypeString;
    int m_strength;
    int m_speed;
    int m_defense;
    int m_reproduction;

    QString playerTypeToString(PlayerType playerType);

signals:
    void pointCountChanged();
    void percentageChanged();
};
#endif // PLAYER_H
