#pragma once

#include "stats.h"

class Achvments
{
public:
    Achvments();
    // Fields to handle with achievements status.
    bool EarnNGold;
    bool EarnNDiamonds;
    bool KillNMonsters;
    bool ReachNStage;
    bool OwnNArtifacts;
    bool HireNSoldiers;
    bool TapNTimes;
    bool HeropowNTimes;
    bool DoNCritical;
    // Function to check if some achievement was accomplished.
    void checkAchievements(Stats *stats);
};
