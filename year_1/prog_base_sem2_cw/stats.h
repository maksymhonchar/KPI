#pragma once

#include <QTime>

#define MULTIPLIER_COST 20

class Stats
{
public:
    Stats();
    // Current status fields.
    int CurrentLevel;
    long long CurrentGold;
    long long CurrentDiamonds;
    long long CurrentTapDamage;
    long long CurrentArmyDamage;
    double CurrentCriticalChance;
    // General status fields.
    int ArmyAmount;
    int ArtifactsUnlocked;
    int AwardsCollected;
    int HeropowersUnlocked;
    // Multipliers.
    double CriticalHitMultiplier;
    double GoldMultiplier;
    double DiamondsMultiplier;
    double MonsterHPDecreaser;
    double PerksCostDecreaser;
    // Total status fields.
    long long TotalGoldCollected;
    int TotalDiamondsCollected;
    int TotalTapsMade;
    int TotalCriticalTapsMade;
    int TotalMonsterKills;
    // Played time field.
    QTime TotalPlayTime;
    int TotalDaysPlayed;

    void checkDayPassed();
};
