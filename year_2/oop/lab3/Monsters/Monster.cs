using System;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// <para>A delegate to hold a function, which invokes, when a monster is hit by hero.</para>
    /// </summary>
    public delegate void monsterHitEventHandler();

    [Serializable]
    public class Monster : Model, IFightable
    {
        /// <summary>
        /// <para>Total amount of monsters.</para>
        /// </summary>
        private static int GlobalMonstersAmount { get; set; }
        
        /// <summary>
        /// <para>Armor value, that belongs to Monster.</para>
        /// </summary>
        protected int Armor;

        /// <summary>
        /// <para>Gold, dropped after killing a Monster.</para>
        /// </summary>
        protected int GoldDrop;

        /// <summary>
        /// <para>An event, which invokes, when a monster gets a hit by someone.</para>
        /// </summary>
        public event monsterHitEventHandler MonsterHit;

        /// <summary>
        /// <para>Basic Monster constructor, that fills all the values in Model parent class and default values in his class</para>
        /// </summary>
        public Monster()
            : base()
        {
            GlobalMonstersAmount++;
            this.GoldDrop = GameUtils.randInt(500, 1000);
            this.Damage = GameUtils.calculateDamageMonster(this.GoldDrop);
            this.Armor = GameUtils.randInt();
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
            Logger.printMsgSystem(String.Format("Monster has received specific name: {0}.", this.Name));
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
                Logger.printMsgSystem("There is no Hero to attack.");
                return;
            }
            // subscribe
            hero.HeroHit += this.prepToFight;
            Logger.printMsgPlayer(String.Format("Monster {0} hits a hero {1}!", this.Name, hero.getName()));
            hero.getDamage(this.Damage, this, hero);
            // unsubscribe. Reason why to clear subscribed reaction from a hero here: it is a protected member.
            hero.HeroHit -= this.prepToFight;
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
                Logger.printMsgSystem("There is no Hero-attacker.");
                return;
            }
            // First, before hit from hero, check if a monster isn't dead yet.
            if (this.Health <= 0)
                throw (new NotAbleToFightException("This monster is already dead - a hero cannot hit him."));

            // invoke all subscribed "reactions" for a hit to monster.
            this.MonsterHit();
            this.Health -= damage;
            Logger.printMsgPlayer(
                String.Format(
                    "Hero {0} dealed {1} damage to monster {2}.",
                    hero.getName(), damage, this.Name));
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
        protected virtual void prepToFight()
        {
            Logger.printMsgPlayer(String.Format("Monster {0} is ready to fight!", this.Name));
        }

        /// <summary>
        /// <para>Get current amount of health out of 100.</para>
        /// </summary>
        /// <returns>Current amount of health.</returns>
        public int getHealth()
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
        public string getName()
        {
            return this.Name;
        }

        public override string ToString()
        {
            return String.Format("Monster {0}. Gold dropped: {1}. Health: {2}.", this.Name, this.GoldDrop, this.Health);
        }
    }
}
