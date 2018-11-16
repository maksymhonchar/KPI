using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    public class Monster : Model, IFightable
    {
        /// <summary>
        /// <para>Total amount of monsters.</para>
        /// </summary>
        private static int GlobalMonstersAmount { get; set; }
        
        /// <summary>
        /// <para>Armor value, that belongs to Monster.</para>
        /// </summary>
        protected int armor;

        /// <summary>
        /// <para>Gold, dropped after killing a Monster.</para>
        /// </summary>
        protected int goldDrop;

        /// <summary>
        /// <para>Basic Monster constructor, that fills all the values in Model parent class and default values in his class</para>
        /// </summary>
        public Monster()
            : base()
        {
            GlobalMonstersAmount += 1;
            this.Damage = GameUtils.calculateDamageMonster(this.goldDrop);
            this.armor = GameUtils.randInt();
            this.goldDrop = GameUtils.randInt(500, 1000);
            Logger.printMsgSystem(String.Format("Monster {0} has been created.", this.Name));
        }

        /// <summary>
        /// <para>Add a specific name, when creating a Monster instance.</para>
        /// </summary>
        /// <param name="name">Specific name for the Monster.</param>
        public Monster(string name)
            : this()
        {
            this.Name = name;
            Logger.printMsgSystem(String.Format("Monster {0} has been created.", this.Name));
        }

        /// <summary>
        /// <para>Deal damage to the hero.</para>
        /// </summary>
        /// <param name="monster">Leave this empty.</param>
        /// <param name="hero">Hero to deal damage.</param>
        public virtual void dealDamage(Monster monster = null, Hero hero = null)
        {
            if (hero == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Hero to attack!");
                return;
            }
            this.prepareToFight();
            Logger.printMsgPlayer(String.Format("Monster {0} is starting hitting a hero {1}!", this.Name, hero.getHeroName()));
            hero.getDamage(this.Damage, monster: this);
        }

        /// <summary>
        /// <para>Get damage (reduce Health) from the hero</para>
        /// </summary>
        /// <param name="damage">Damage to get from Hero.</param>
        /// <param name="monster">Leave it empty.</param>
        /// <param name="hero">Hero get damage from.</param>
        public virtual void getDamage(int damage, Monster monster = null, Hero hero = null)
        {
            if (hero == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Hero to get damage from!");
                return;
            }
            this.Health -= damage - (int)(this.armor * 0.25);
            Logger.printMsgPlayer(
                String.Format(
                    "Arrrgh, hero {0} dealed {1} damage to me, {2}!",
                    hero.getHeroName(), damage, this.Name));
        }

        /// <summary>
        /// <para>Deal a critical damage to the Monster.</para>
        /// <see cref="SwordsMan" text=" - Overridden in SwordsMan class."/>
        /// </summary>
        /// <param name="monster">Monster that deals a critical damage.</param>
        /// <param name="hero">Hero, that hits a monster.</param>
        public virtual void doCritical(Monster monster = null, Hero hero = null)
        {
            Logger.printMsgSystem("This monster cannot use a critical hit ability.");
        }

        /// <summary>
        /// <para>Print a greetings, when Monster starts to deal/become damage.</para>
        /// </summary>
        protected virtual void prepareToFight()
        {
            Logger.printMsgPlayer(String.Format("Monster {0} is ready to fight!", this.Name));
        }

        /// <summary>
        /// <para>Get current amount of health out of 100.</para>
        /// </summary>
        /// <returns>Current amount of health.</returns>
        public int getCurrentHealth()
        {
            return this.Health;
        }

        /// <summary>
        /// <para>Get a Hero name.</para>
        /// <seealso cref="Hero.dealDamage(Monster, Hero)"/>
        /// <para></para>
        /// <seealso cref="Hero.getDamage(int, Monster, Hero)"/>
        /// </summary>
        /// <returns>Monsters name.</returns>
        public string getMonsterName()
        {
            return this.Name;
        }

        public override string ToString()
        {
            return String.Format("Monster {0}. Gold dropped: {1}. Has {2} armor.", this.Name, this.goldDrop, this.armor);
        }
    }
}
