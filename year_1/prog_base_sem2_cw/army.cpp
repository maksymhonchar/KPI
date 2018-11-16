#include <QFile>
#include <QTextStream>

#include "army.h"

Army::Army()
{
    // Parse data from army.csv to army types array.
    // Data in .csv is represented in format [name-price-DPS].
    QFile file(":/data/data/army.csv");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line = "";
    int i = 0;
    while((line = in.readLine()) != NULL)
    {
        QStringList data = line.split(',');
        this->army[i].Name = data[0];
        this->army[i].Price = data[1].toInt();
        this->army[i++].DPS = data[2].toInt();
    }
    // As default, user does not have any soldiers.
    // Fill soldiersAmount array with zeros.
    memset(this->soldiersAmount, 0, SOLDIERS_AMOUNT * sizeof(int));
}

int Army::getArmyDamage()
{
    // Go through army and count total DPS.
    int totalDPS = 0;
    for(int i = 0; i < SOLDIERS_AMOUNT; i++)
    {
        totalDPS += this->army[i].DPS * this->soldiersAmount[i];
    }
    return (totalDPS);
}

int Army::getArmyAmount()
{
    // Count total amount of soldiers in whole army.
    int totalAmount = 0;
    for(int i = 0; i < SOLDIERS_AMOUNT; i++)
    {
        totalAmount += this->soldiersAmount[i];
    }
    return (totalAmount);
}
