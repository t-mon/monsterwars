#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QDebug>

class Monster;
class Player;

class Level: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int levelId READ levelId NOTIFY levelIdChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

public:
    explicit Level(QObject *parent = 0);
    ~Level();

    void setName(const QString &name);
    QString name() const;

    void setLevelId(const int &levelId);
    int levelId() const;

    void setMonstersVariants(const QVariantList &monstersVariant);
    QVariantList monstersVariant() const;

    void setPlayersVariants(const QVariantList &playersVariant);
    QVariantList playersVariant() const;

private:
    QVariantList m_monstersVariant;
    QVariantList m_playersVariant;
    QString m_name;
    int m_levelId;

signals:
    void levelIdChanged();
    void nameChanged();

};
#endif // LEVEL_H
