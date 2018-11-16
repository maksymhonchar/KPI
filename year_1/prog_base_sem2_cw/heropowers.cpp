#include "heropowers.h"

HeroPowers::HeroPowers()
{
    this->anduinTimer = new QTimer();
    this->sylvanasTimer = new QTimer();
    this->guldanTimer = new QTimer();
    this->artasTimer = new QTimer();

    this->anduinBought = false;
    this->sylvanasBought = false;
    this->guldanBought = false;
    this->artasBought = false;

    this->anduinCD = false;
    this->sylvanasCD = false;
    this->guldanCD = false;
    this->artasCD = false;
}

void HeroPowers::refreshCD()
{
    this->anduinCD = true;
    this->sylvanasCD = true;
    this->guldanCD = true;
    this->artasCD = true;
}
