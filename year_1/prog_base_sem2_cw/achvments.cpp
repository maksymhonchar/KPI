#include "achvments.h"
#include "stats.h"

#define N_GOLD 1000
#define N_DIAMONDS 1000
#define N_MONSTERS_KILLED 100
#define N_LEVELS_COMPLETED 100
#define N_ARTIFACTS_OWNED 50
#define N_SOLDIERS_HIRED 1000
#define N_TIMES_TAPPED 1000
#define N_HEROPOWERS_USED 10
#define N_CRITICAL 0.25

Achvments::Achvments()
{
    // As default, all achievements are locked.
    this->EarnNGold = false;
    this->EarnNDiamonds = false;
    this->KillNMonsters = false;
    this->ReachNStage = false;
    this->OwnNArtifacts = false;
    this->HireNSoldiers = false;
    this->TapNTimes = false;
    this->HeropowNTimes = false;
    this->DoNCritical = false;
}

void Achvments::checkAchievements(Stats *stats)
{
    if(stats->TotalGoldCollected >= N_GOLD && !this->EarnNGold) {
        this->EarnNGold = true;
        stats->AwardsCollected++;
    }
    if(stats->TotalDiamondsCollected >= N_DIAMONDS && !this->EarnNDiamonds) {
        this->EarnNDiamonds = true;
        stats->AwardsCollected++;
    }
    if(stats->TotalMonsterKills >= N_MONSTERS_KILLED && !this->KillNMonsters) {
        this->KillNMonsters = true;
        stats->AwardsCollected++;
    }
    if(stats->CurrentLevel >= N_LEVELS_COMPLETED && !this->ReachNStage) {
        this->ReachNStage = true;
        stats->AwardsCollected++;
    }
    if(stats->ArtifactsUnlocked >= N_ARTIFACTS_OWNED && !this->OwnNArtifacts) {
        this->OwnNArtifacts = true;
        stats->AwardsCollected++;
    }
    if(stats->ArmyAmount >= N_SOLDIERS_HIRED && !this->HireNSoldiers) {
        this->HireNSoldiers = true;
        stats->AwardsCollected++;
    }
    if(stats->TotalTapsMade >= N_TIMES_TAPPED && !this->TapNTimes) {
        this->TapNTimes = true;
        stats->AwardsCollected++;
    }
    if(stats->HeropowersUnlocked >= N_HEROPOWERS_USED && !this->HeropowNTimes) {
        this->HeropowNTimes = true;
        stats->AwardsCollected++;
    }
    if(stats->CurrentCriticalChance >= N_CRITICAL && !this->DoNCritical) {
        this->DoNCritical = true;
        stats->AwardsCollected++;
    }
}
