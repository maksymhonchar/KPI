using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    interface IFightable
    {
        void dealDamage(Monster monster = null, Hero hero = null);
        void getDamage(int damage, Monster monster = null, Hero hero = null);
        void doCritical(Monster monster = null, Hero hero = null);
    }
}
