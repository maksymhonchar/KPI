using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to represent a casual monster.</para>
    /// <para>Casual Monster has twice less damage, than default Monster.</para>
    /// <para>Casual Monster cannot do a critical hit. Instead Monster.doCritical() will be invoked.</para>
    /// </summary>
    public class CasualMonster : Monster
    {
        /// <summary>
        /// <para>Default constructor, that fills only Damage field.</para>
        /// </summary>
        public CasualMonster() 
            : base()
        {
            this.Damage /= 2;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.dealDamage(Monster, Hero)"/>
        /// </summary>
        public override void dealDamage(Monster monster = null, Hero hero = null)
        {
            if (hero == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Hero to attack!");
                return;
            }
            this.prepareToFight();
            Logger.printMsgPlayer("Arggh, Casual Monster is attacking!");
            hero.getDamage(this.Damage, monster: this);
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.getDamage(int, Monster, Hero)"/>
        /// </summary>
        public override void getDamage(int damage, Monster monster = null, Hero hero = null)
        {
            if (hero == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Hero to get damage from!");
                return;
            }
            Logger.printMsgPlayer("Arggh, Casual Monster got damaged...");
            this.Health -= damage - (int)(this.armor * 0.25);
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.prepareToFight()"/>
        /// </summary>
        protected override void prepareToFight()
        {
            Logger.printMsgPlayer("Casual monster is ready to fight!");
        }

        public override string ToString()
        {
            return String.Format("Arrrgh, I will kill you! By the way, my name is {0}.", this.Name);
        }
    }
}
