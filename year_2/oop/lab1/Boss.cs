using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to represent a Boss - specific type of Monster.</para>
    /// <para>This class differs from basic Monster, that it can do a strong critical hit. Also he has a jewel drop, not only a gold drop, as a Monster.</para>
    /// <para>doCritical(int, monster, hero) - overridden method.</para>
    /// <para>dealDamage(monster, hero) - overridden method.</para>
    /// <para>getDamage(damage, monster, hero) - overridden method.</para>
    /// <para>prepareToFight() - overridden method.</para>
    /// <para>doCritical(int, monster, hero) - overridden method.</para>
    /// <para>toString() - overridden method.</para>
    /// </summary>
    public class Boss : Monster
    {
        /// <summary>
        /// <para>A chance to deal a stronger hit to hero.</para>
        /// </summary>
        private double criticalChance;

        /// <summary>
        /// <para>Jewellery to drop after death of Boss.</para>
        /// </summary>
        private int jewelDrop;

        /// <summary>
        /// <para>Sole constructor to create a Boss as a Monster, but with specific name, critical chance and a jewellery drop value.</para>
        /// </summary>
        /// <param name="name">Name for the Boss.</param>
        public Boss(string name)
            : base(name)
        {
            this.criticalChance = GameUtils.randDouble();
            this.jewelDrop = GameUtils.randInt(max: 10);
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
            Logger.printMsgPlayer("Arggh, BOSS is attacking!");
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
            Logger.printMsgPlayer("Arggh, BOSS got damaged...");
            this.Health -= 1;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.prepareToFight()"/>
        /// </summary>
        protected override void prepareToFight()
        {
            Logger.printMsgPlayer(String.Format("BOSS: I WILL CRUSH YOU!"));
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
            Logger.printMsgSystem(String.Format("Monster {0} did a critical damage to {1}!", this.Name, hero.getHeroName()));
            int criticalDamageToDeal = (int)(this.Damage * this.criticalChance) + this.Damage;
            hero.getDamage(criticalDamageToDeal, monster: this);
        }

        public override string ToString()
        {
            return String.Format("Hello, I am a boss {0}. Armor: {1}. Critical hit chance: {2:.2}.", this.Name, this.armor, this.criticalChance);
        }

    }
}
