#pragma once

#define SOLDIERS_AMOUNT 10

class Army
{
public:
    Army();
    // Structure to describe soldier type.
    // This data is used in total army damage calculation and
    // in filling army labels in GUI.
    struct Soldier_S
    {
        QString Name;
        int Price;
        int DPS;
    };
    // An array to describe all soldier types.
    // Each cell contains different soldier type.
    Soldier_S army[SOLDIERS_AMOUNT];
    // An array to describe soldiers amount.
    // Each cell contains amount of certain soldier type.
    int soldiersAmount[SOLDIERS_AMOUNT];
    // Count total army damage.
    int getArmyDamage();
    // Count total soldiers amount.
    int getArmyAmount();
};
