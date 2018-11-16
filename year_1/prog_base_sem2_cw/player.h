#pragma once

#include <QString>
#include <QTime>

class Player
{
public:
    Player(QString name, int level, int tapDmg, QTime *timePlayed);
    QString name;
    int level;
    int tapDmg;
    QTime *timePlayed;
};
