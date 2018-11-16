#pragma once

#include <QString>

class GameInfo
{
public:
    GameInfo(QString playerName);

    bool firstLaunch;
    QString playerName;
    int positionInRank;
};
