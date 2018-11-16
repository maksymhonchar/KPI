using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    // TOASK: which is better - base.field, or this.field?
    // TOASK: here I wanted to implement Interface function doCritical() in a child. Is that really possible?
    // TODO: event, if all dragons are defeated - call a greetings func.

    /// <summary>
    /// <para>Class to represent a Hero instance.</para>
    /// <para>Hero has a sword, backpack objects, level and a lifetime.</para>
    /// </summary>
    public class Hero : Model, IFightable
    {
        /// <summary>
        /// <para>Life time of the Hero during the game process.</para>
        /// </summary>
        private readonly DateTime lifeTime;

        /// <summary>
        /// <para>Heroes backpack with items. Damage depends on the backpack. Is printed in the ToString().</para>
        /// </summary>
        protected string[] backpack;

        /// <summary>
        /// <para>Heroes sword. Damage depends on the sword. Is printed in the ToString().</para>
        /// </summary>
        protected string sword;

        /// <summary>
        /// <para>Level of the Hero. Is printed in the ToString().</para>
        /// </summary>
        protected int level;

        /// <summary>
        /// <para>Basic Hero constructor, that fills all the values in Model parent class and default values in his class</para>
        /// </summary>
        public Hero()
            : base()
        {
            this.lifeTime = DateTime.Now;
            this.backpack = GameUtils.createBackPack();
            this.sword = GameUtils.createSword();
            this.Damage = GameUtils.calculateDamageHero(this.backpack, this.sword);
            this.level = 1;
            Logger.printMsgSystem(String.Format("Hero {0} has been created.", this.Name));
        }

        /// <summary>
        /// <para>Add a specific name, when creating a Hero instance.</para>
        /// </summary>
        /// <param name="name">Specific name for the Hero.</param>
        public Hero(string name)
            : this()
        {
            this.Name = name;
            Logger.printMsgSystem(String.Format("Hero {0} has been created.", this.Name));
        }

        /// <summary>
        /// <para>Deal damage to the Monster.</para>
        /// <para>Usage: you can leave Hero object empty and only pass a Monster instance as an argument.</para>
        /// </summary>
        /// <param name="monster">Monster to deal damage.</param>
        /// <param name="hero">Leave it empty.</param>
        public virtual void dealDamage(Monster monster = null, Hero hero = null)
        {
            if (monster == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Monster to attack!");
                return;
            }
            this.prepareToFight();
            Logger.printMsgPlayer(String.Format("Hero {0} is starting hitting a monster {1}!", this.Name, monster.getMonsterName()));
            monster.getDamage(this.Damage, hero: this);
        }

        /// <summary>
        /// <para>Get damage from the Monster.</para>
        /// <para>Usage: you can leave Hero object empty and only pass a Monster instance and damage as arguments.</para>
        /// </summary>
        /// <param name="damage">Damage to be taken.</param>
        /// <param name="monster">Monster to take damage from.</param>
        /// <param name="hero">Leave it empty.</param>
        public virtual void getDamage(int damage, Monster monster = null, Hero hero = null)
        {
            if (monster == null)
            {
                Logger.printMsgSystem("Sorry, but there is no Monster to get damage from!");
                return;
            }
            this.Health -= damage;
            Logger.printMsgPlayer(
                String.Format(
                    "Oh no, monster {0} dealed {1} damage to me, {2}!",
                    monster.getMonsterName(), damage, this.Name));
        }
        
        /// <summary>
        /// <para>Deal a critical damage to the Monster.</para>
        /// <see cref="SwordsMan" text=" - Overridden in SwordsMan class."/>
        /// </summary>
        /// <param name="monster">Monster, that Hero hits.</param>
        /// <param name="hero">Hero, that deals critical damage.</param>
        public virtual void doCritical(Monster monster = null, Hero hero = null)
        {
            Logger.printMsgSystem("This hero cannot use a critical hit ability.");
        }

        /// <summary>
        /// <para>Print a greetings, when Hero starts to deal/become damage.</para>
        /// </summary>
        protected virtual void prepareToFight()
        {
            Logger.printMsgPlayer(String.Format("Hero {0} is ready to fight!", this.Name));
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
        /// <seealso cref="Monster.dealDamage(Monster, Hero)"/>
        /// <para></para>
        /// <seealso cref="Monster.getDamage(int, Monster, Hero)"/>
        /// </summary>
        /// <returns>Hero name.</returns>
        public string getHeroName()
        {
            return this.Name;
        }

        public override string ToString()
        {
            return String.Format("Hero {0}. Level {1}. Has {2} items in backpack. Sword: {3}. Created at {4}.", this.Name, this.level, this.backpack.Length, this.sword, this.lifeTime);
        }
    }
}
