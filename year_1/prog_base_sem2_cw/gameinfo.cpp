#include "gameinfo.h"

#define LAST_POSITION 10

GameInfo::GameInfo(QString playerName)
{
    this->firstLaunch = false;
    this->playerName = playerName;
    this->positionInRank = LAST_POSITION;
}
