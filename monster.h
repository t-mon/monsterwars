#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QColor>

#include "particlecloud.h"


class GameEngine;
class Player;
class Node;

class Monster : public QObject
{
    Q_OBJECT
    Q_ENUMS(MonsterType)
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString colorString READ colorString NOTIFY colorStringChanged)
    Q_PROPERTY(QString monsterTypeString READ monsterTypeString CONSTANT)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(int value READ value NOTIFY valueChanged)
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool selected READ selected NOTIFY selectedChanged)

public:
    enum MonsterType{
        MonsterTypeNormal,
        MonsterTypeStrength,
        MonsterTypeReproduction,
        MonsterTypeDefense,
        MonsterTypeSpeed
    };

    explicit Monster(GameEngine *engine,
                   MonsterType monsterType = MonsterTypeNormal,
                   int id = -1,
                   int startValue = 0,
                   QPoint position = QPoint(),
                   QString colorString = "white",
                   QObject *parent = 0);

    Monster(GameEngine* engine, int startValue);

    void setMonsterType(const MonsterType &monsterType);
    bool setMonsterType(const QString &monsterType);

    MonsterType monsterType() const;
    QString monsterTypeString() const;

    void setPlayer(Player* player);
    Player *player() const;

    void setId(const int &id);
    int id() const;

    int value() const;

    int size() const;
    void setSize(const int &size);

    void setPosition(const QPoint &position);
    QPoint position() const;

    void setColorString(const QString &colorString);
    QString colorString() const;

    void select(const bool &selected);
    bool selected() const;

    int split();
    void impact(ParticleCloud *particleCloud);

private:
    GameEngine *m_engine;
    Player *m_player;
    MonsterType m_monsterType;
    QString m_monsterTypeString;
    int m_id;
    int m_value;
    int m_size;
    int m_maxValue;
    QPoint m_position;
    QString m_colorString;
    bool m_selected;
    int m_tickCounter;

    QString monsterTypeToString(MonsterType monsterType);

signals:
    void valueChanged();
    void sizeChanged();
    void positionChanged();
    void colorStringChanged();
    void selectedChanged();
    void playerChanged();
    void impact();

private slots:
    void slotTick();
};
#endif // MONSTER_H
