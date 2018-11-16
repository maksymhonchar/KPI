using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to represent a SwordsMan - specific type of Hero.</para>
    /// <para>This class differs from basic Hero, that it can do a strong critical hit.</para>
    /// <para>doCritical(int, monster, hero) - overridden method.</para>
    /// <para>dealDamage(monster, hero) - overridden method.</para>
    /// <para>getDamage(damage, monster, hero) - overridden method.</para>
    /// <para>prepareToFight() - overridden method.</para>
    /// <para>doCritical(int, monster, hero) - overridden method.</para>
    /// <para>toString() - overridden method.</para>
    /// </summary>
    public class SwordsMan : Hero
    {
        /// <summary>
        /// <para>A chance to deal a stronger hit to monster.</para>
        /// </summary>
        private double criticalChance;

        /// <summary>
        /// <para>Constructor to create a SwordsMan as a Hero, but with specific name and critical chance.</para>
        /// </summary>
        /// <param name="name">Name for the SwordsMan.</param>
        public SwordsMan(string name)
            : base(name)
        {
            this.criticalChance = GameUtils.randDouble();
            this.Name = name;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.dealDamage(Monster, Hero)"/>
        /// </summary>
        public override void dealDamage(Monster monster = null, Hero hero = null)
        {
            this.prepareToFight();
            Logger.printMsgPlayer("Ha-Ha, our Swordsman is attacking!");
            monster.getDamage(this.Damage, hero: this);
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.getDamage(int, Monster, Hero)"/>
        /// </summary>
        public override void getDamage(int damage, Monster monster = null, Hero hero = null)
        {
            Logger.printMsgPlayer("Oh no, our SwordsMan has been damaged!");
            this.Health -= 1;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.prepareToFight()"/>
        /// </summary>
        protected override void prepareToFight()
        {
            Logger.printMsgPlayer(String.Format("Swordsman is ready to fight!"));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.doCritical(Monster, Hero)"/>
        /// </summary>
        public override void doCritical(Monster monster = null, Hero hero = null)
        {
            if (monster == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Monster to attack!");
                return;
            }
            Logger.printMsgSystem(String.Format("Hero {0} did a critical damage to {1}!", this.Name, monster.getMonsterName()));
            int criticalDamageToDeal = (int)(this.Damage * this.criticalChance) + this.Damage;
            monster.getDamage(criticalDamageToDeal, hero: this);
        }

        public override string ToString()
        {
            return String.Format("Hero {0}. Level {1}. Has {2} items in backpack. Sword: {3}. Critical damage: {4:.2}.", this.Name, this.level, this.backpack.Length, this.sword, this.criticalChance);
        }
    }
}
