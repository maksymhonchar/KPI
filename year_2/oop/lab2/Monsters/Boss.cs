using System;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// <para>Class to represent a Boss - specific type of Monster.</para>
    /// <para>This class differs from basic Monster, that it can do a strong critical hit. Also he has a jewel drop, not only a gold drop, as a Monster.</para>
    /// </summary>
    public class Boss : Monster
    {
        /// <summary>
        /// <para>A chance to deal a stronger hit to hero.</para>
        /// </summary>
        private double CriticalChance;

        /// <summary>
        /// <para>Jewellery to drop after death of Boss.</para>
        /// </summary>
        private int JewelDrop;

        /// <summary>
        /// <para>Sole constructor to create a Boss as a Monster, but with specific name, critical chance and a jewellery drop value.</para>
        /// </summary>
        /// <param name="name">Name for the Boss.</param>
        public Boss(string name)
            : base(name)
        {
            this.CriticalChance = GameUtils.randDouble();
            this.JewelDrop = GameUtils.randInt(max: 10);
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.doCritical(Monster, Hero)"/>
        /// </summary>
        public override void doCritical(Monster monster = null, Hero hero = null)
        {
            if (hero == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Hero to attack!");
                return;
            }
            // subscribe.
            hero.HeroHit += this.prepToFight;
            Logger.printMsgSystem(String.Format("Boss {0} does a critical damage to {1}!", this.Name, hero.getName()));
            int criticalDamageToDeal = (int)(this.Damage * this.CriticalChance) + this.Damage;
            hero.getDamage(criticalDamageToDeal, this, hero);
            // unsubscribe. Reason why to clear subscribed reaction from a monster here: it is a protected member.
            hero.HeroHit-= this.prepToFight;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.prepToFight()"/>
        /// </summary>
        protected override void prepToFight()
        {
            Logger.printMsgPlayer(String.Format("BOSS: I WILL CRUSH YOU!"));
        }

        public override string ToString()
        {
            return String.Format("A boss {0}. Armor: {1}. Health: {2}. Critical hit chance: {3:.2}.", this.Name, this.Armor, this.Health, this.CriticalChance);
        }
    }
}
