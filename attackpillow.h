#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QDebug>
#include <QColor>
#include <QUuid>

class Player;
class Monster;

class AttackPillow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(int speed READ speed CONSTANT)
    Q_PROPERTY(QString colorString READ colorString CONSTANT)

    Q_PROPERTY(Monster *sourceMonster READ sourceMonster CONSTANT)
    Q_PROPERTY(Monster *destinationMonster READ destinationMonster CONSTANT)

public:
    explicit AttackPillow(Player* player, Monster *sourceMonster, Monster *destinationMonster, int count, int strength, int speed, QObject *parent = 0);

    QUuid id() const;

    Player *player() const;
    Monster *sourceMonster() const;
    Monster *destinationMonster() const;

    int count() const;
    QString colorString() const;
    int strength() const;
    int speed() const;

private:
    QUuid m_id;
    Player *m_player;
    Monster *m_sourceMonster;
    Monster *m_destinationMonster;
    int m_count;
    int m_strength;
    int m_speed;

};
#endif // PARTICLE_H
