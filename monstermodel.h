#ifndef MONSTERMODEL_H
#define MONSTERMODEL_H

#include <QAbstractListModel>

#include "monster.h"

class MonsterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MonsterRole {
        IdRole,
        ValueRole,
        ColorStringRole,
        MonsterTypeRole,
        SizeRole,
        PositionXRole,
        PositionYRole,
        SelectedRole
    };

    explicit MonsterModel(QObject *parent = 0);

    QList<Monster *> monsters();
    Monster *monsterWithId(int id);

    void impact(Monster *monster, AttackPillow *pillow);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addMonster(Monster *monster);
    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Monster *> m_monsters;
    int indexOf(Monster *monster);

private slots:
    void monsterValueChanged();
    void monsterColorChanged();
    void monsterSelectedChanged();
};

#endif // MONSTERMODEL_H
