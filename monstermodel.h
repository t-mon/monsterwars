#ifndef MONSTERMODEL_H
#define MONSTERMODEL_H

#include <QAbstractListModel>

class MonsterModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MonsterModel(QObject *parent = 0);

signals:

public slots:

};

#endif // MONSTERMODEL_H
