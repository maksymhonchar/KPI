#include "player.h"

Player::Player(QString name, int level, int tapDmg, QTime *timePlayed)
{
    this->name = name;
    this->level = level;
    this->tapDmg = tapDmg;
    this->timePlayed = timePlayed;
}
