#include "attack.h"

Attack::Attack(QObject *parent):
    QObject(parent)

{
}

void Attack::beginnAttack(int id)
{
    m_sourceIds.append(id);
}

void Attack::endAttack(int id)
{
    for (int i = 0; i < m_sourceIds.count(); i++) {
        if( m_sourceIds.at(i) == id) {
            m_sourceIds.removeAt(i);
        }
    }
    m_destinationId = id;
    emit attackFinished();
}

QList<int> Attack::sourceIds()
{
    return m_sourceIds;
}

int Attack::destinationId()
{
    return m_destinationId;
    emit attackFinished();
}

void Attack::addMonsterId(int id)
{
    if(m_sourceIds.contains(id))
        return;

    m_sourceIds.append(id);
}

void Attack::reset()
{
    m_sourceIds.clear();
    m_destinationId = -1;
}
