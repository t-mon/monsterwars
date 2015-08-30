#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QDebug>

class Monster;
class Player;

class Level: public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);
    ~Level();

    void setName(const QString &name);
    QString name() const;

    void setLevelId(const int &levelId);
    int levelId() const;

    void addMonster(Monster *monster);
    QList<Monster *> monsteres() const;
    Monster* monster(int id) const;

    void addPlayer(Player *player);
    QList<Player *> players() const;
    Player *player(int id) const;

private:
    QList<Monster *> m_monsteres;
    QList<Player *> m_players;
    QString m_name;
    int m_levelId;

};
#endif // LEVEL_H
