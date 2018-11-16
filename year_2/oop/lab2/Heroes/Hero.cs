using System;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// <para>A delegate to hold a function, which invokes, when a hero is hit by monster.</para>
    /// </summary>
    public delegate void heroHitEventHandler();

    /// <summary>
    /// Class to represent a Hero instance.
    /// </summary>
    public class Hero : Model, IFightable, IDestructable
    {
        /// <summary>
        /// <para>Heroes backpack with items. Damage depends on the backpack. Is printed in the ToString().</para>
        /// </summary>
        protected GenericList<GameItem> BackPack;

        /// <summary>
        /// <para>An event, which invokes, when a monster gets hit by someone.</para>
        /// </summary>
        public event heroHitEventHandler HeroHit;

        /// <summary>
        /// <para>Basic Hero constructor, that fills all the values in Model parent class and default values in his class</para>
        /// </summary>
        public Hero()
        {
            this.BackPack = GameUtils.fillUpBackPack();
            this.Damage = GameUtils.calculateDamageHero(this.BackPack);
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
            // subscribe
            monster.MonsterHit += this.prepToFight;
            Logger.printMsgPlayer(String.Format("Hero {0} is starting hitting a monster {1}!", this.Name, monster.getName()));
            monster.getDamage(this.Damage, monster, this);
            // unsubscribe. Reason why to clear subscribed reaction from a monster here: it is a protected member.
            monster.MonsterHit -= this.prepToFight;
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
            // First, before hit from monster, check if a hero isn't dead yet.
            try
            {
                if (this.Health <= 0)
                    throw new NotImplementedException();
            }
            catch (Exception ex)
            {
                throw (new NotAbleToFightException("This hero is already dead - a monster cannot hit him.", ex));
            }

            // invoke all subscribed "reactions" for a hit to hero.
            this.HeroHit();
            this.Health -= damage;
            Logger.printMsgPlayer(
                String.Format("Damn, monster {0} dealed {1} damage to {2}!",
                    monster.getName(), damage, this.Name));
            if (this.Health <= 0)
            {
                this.die();
            }
            else if (this.Health <= 20)
            {
                this.beforeDie();
            }
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
        /// <para>Action, when Hero instance is dying.</para>
        /// </summary>
        public virtual void die()
        {
            Logger.printMsgGame(String.Format("The hero {0} died.", this.Name));
        }

        /// <summary>
        /// <para>Make some behavior, when Hero is just about to die.</para>
        /// </summary>
        public virtual void beforeDie()
        {
            Logger.printMsgPlayer(String.Format("The hero {0} is about to die.", this.Name));
        }

        /// <summary>
        /// <para>Print a greetings, when Hero starts to deal/become damage.</para>
        /// </summary>
        protected virtual void prepToFight()
        {
            Logger.printMsgPlayer(String.Format("Hero {0} is ready to fight!", this.Name));
        }

        /// <summary>
        /// <para>Get current amount of health out of 100.</para>
        /// </summary>
        public int getHealth()
        {
            return this.Health;
        }

        /// <summary>
        /// <para>Get a Hero name.</para>
        /// </summary>
        public string getName()
        {
            return this.Name;
        }

        public override string ToString()
        {
            return String.Format("Hero {0}. Has {1} items in backpack. Health: {2}.", this.Name, this.BackPack.getSize(), this.Health);
        }
    }
}
