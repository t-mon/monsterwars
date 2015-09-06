#ifndef ATTACKPILLOWMODEL_H
#define ATTACKPILLOWMODEL_H

#include <QAbstractListModel>

#include "attackpillow.h"

class AttackPillowModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PillowRole {
        ValueRole = Qt::DisplayRole,
        ColorStringRole,
        SpeedRole,
        IdRole,
        SourceXRole,
        SourceYRole,
        DestinationXRole,
        DestinationYRole
    };

    explicit AttackPillowModel(QObject *parent = 0);

    QList<AttackPillow *> pillows();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addPillow(AttackPillow *pillow);
    void removePillow(AttackPillow *pillow);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<AttackPillow *> m_pillows;
    int m_stepSize;
    int m_currentItemIdex;

    int indexOf(AttackPillow *pillow);

signals:
    void pillowListChanged();


public slots:

};

#endif // ATTACKPILLOWMODEL_H
