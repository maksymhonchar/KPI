#include "enemy.h"
#include "stats.h"

#include <limits.h>

Enemy::Enemy(int CurrentLevel)
{
    TotalHP = CurrentLevel;
    CurrentHP = 1;
    GoldDropped = 0;
    DiamondsDropped = 0;
}

Enemy::Enemy(int currentHP, int goldDropped, int diamondsDropped, int totalHP)
{
    this->CurrentHP = currentHP;
    this->GoldDropped = goldDropped;
    this->DiamondsDropped = diamondsDropped;
    this->TotalHP = totalHP;
}

void Enemy::goToNextDragon(Stats *stats)
{
    // Update current and global state fields.
    stats->CurrentGold += ( GoldDropped + stats->GoldMultiplier * GoldDropped );
    if (stats->CurrentGold <= 0) {
        stats->CurrentGold = LONG_MAX - 10000;
    }
    stats->CurrentDiamonds += ( DiamondsDropped + stats->DiamondsMultiplier * DiamondsDropped );
    stats->TotalGoldCollected += GoldDropped;
    if (stats->TotalGoldCollected <= 0) {
        stats->TotalGoldCollected = LONG_MAX - 10000;
    }
    stats->TotalDiamondsCollected += DiamondsDropped;
    stats->TotalMonsterKills++;
    stats->CurrentLevel++;
    // Generate new dragon.
    TotalHP = 5 + (long long) pow(stats->CurrentLevel, 1.80);
    TotalHP -= (long long) TotalHP * stats->MonsterHPDecreaser;
    CurrentHP = TotalHP;
    GoldDropped = (long long)TotalHP * 0.75;
    DiamondsDropped = (stats->CurrentLevel % 10 == 0) ? 1 : 0;
}

bool Enemy::doDamage(int inDamage)
{
    this->CurrentHP -= inDamage;
    return (this->CurrentHP <= 0);
}

bool Enemy::doTapDamage(Stats *stats)
{
    int randomNum = qrand() % 100;
    if(randomNum <= stats->CurrentCriticalChance * 100) {
        this->CurrentHP -= stats->CurrentTapDamage * (5 - 1);
        stats->TotalCriticalTapsMade++;
    }
    stats->TotalTapsMade++;
    this->CurrentHP -= stats->CurrentTapDamage;
    return (this->CurrentHP <= 0);
}
