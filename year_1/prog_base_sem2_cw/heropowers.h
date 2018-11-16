#pragma once

#include <QTimer>

//
#define TAPDMG_UPGRADE_COST 20
#define ANDUIN_UPGRADE_COST 3000
#define SYLVANAS_UPGRADE_COST 3000
#define GULDAN_UPGRADE_COST 5000
#define ARTAS_UPGRADE_COST 3000

//
#define TAPDMG_UPGRADE_VALUE 1
#define ANDUIN_UPGRADE_VALUE 3
#define SYLVANAS_UPGRADE_VALUE 0.25
#define GULDAN_UPGRADE_VALUE 500
#define ARTAS_UPGRADE_VALUE 50

//
#define ANDUIN_DURATION_MS 5000
#define SYLVANA_DURATION_MS 10000
#define GULDAN_DURATION_MS 5000
#define ARTAS_DURATION_MS 5000

class HeroPowers
{

public:
    HeroPowers();
    void refreshCD();

    // Timers to track time, when certain heropowers should end their actions.
    QTimer *anduinTimer;
    QTimer *sylvanasTimer;
    QTimer *guldanTimer;
    QTimer *artasTimer;

    // Fields to check if some heropower was bought.
    bool anduinBought;
    bool sylvanasBought;
    bool guldanBought;
    bool artasBought;

    // Fields to handle with heropowers cooldowns.
    bool anduinCD;
    bool sylvanasCD;
    bool guldanCD;
    bool artasCD;
};
