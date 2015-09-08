#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    QString playerColor() const;
    void setPlayerColor(const QString &colorString);

signals:

public slots:

};

#endif // SETTINGS_H
