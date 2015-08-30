#ifndef ATTACK_H
#define ATTACK_H

#include <QObject>
#include <QDebug>

class Attack : public QObject
{
    Q_OBJECT

public:
    explicit Attack(QObject *parent = 0);

    void beginnAttack(int id);
    void endAttack(int id);
    QList<int> sourceIds();
    int destinationId();
    void addMonsterId(int id);
    void reset();

private:
    QList<int> m_sourceIds;
    int m_destinationId;
    int m_currentId;

signals:
    void attackFinished();

};
#endif // ATTACK_H
