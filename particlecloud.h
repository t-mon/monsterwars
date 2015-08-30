#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QDebug>
#include <QColor>

class Player;

class ParticleCloud : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x NOTIFY xChanged)
    Q_PROPERTY(int y READ y NOTIFY yChanged)

public:
    explicit ParticleCloud(Player* player, int count, int strength, int speed, int x, int y, QObject *parent = 0);

    Player *player() const;
    int count() const;
    QString colorString() const;
    int strength() const;
    int speed() const;
    int x();
    int y();

private:
    Player* m_player;
    int m_count;
    int m_strength;
    int m_speed;
    int m_x;
    int m_y;

signals:
    void xChanged();
    void yChanged();

};
#endif // PARTICLE_H
