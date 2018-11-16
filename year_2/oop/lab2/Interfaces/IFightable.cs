using System;

namespace MonstersHeroesEmulator
{
    interface IFightable
    {
        void dealDamage(Monster monster = null, Hero hero = null);
        void getDamage(int damage, Monster monster = null, Hero hero = null);
        void doCritical(Monster monster = null, Hero hero = null);
    }
}
