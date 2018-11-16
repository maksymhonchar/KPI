using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Soap;


namespace MonstersHeroesEmulator
{
    /// <summary>
    /// Class to represent a SwordsMan - specific type of Hero.
    /// This class differs from basic Hero, that it can do a strong critical hit.
    /// </summary>
    [Serializable]
    public class SwordsMan : Hero, IDisposable
    {
        /// <summary>
        /// <para>A dump for the GC show case.</para>
        /// </summary>
        public List<decimal> dump;

        /// <summary>
        /// <para>A chance to deal a stronger hit to monster.</para>
        /// </summary>
        private double CriticalChance;

        /// <summary>
        /// <para>Constructor to create a SwordsMan as a Hero, but with specific name and critical chance.</para>
        /// </summary>
        /// <param name="name">Name for the SwordsMan.</param>
        public SwordsMan(string name)
            : base(name)
        {
            this.CriticalChance = GameUtils.randDouble();
            this.Name = name;
            dump = new List<decimal>();
        }

        ~SwordsMan()
        {
            Console.WriteLine("Deleting a swordsman...");
            Dispose();
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.doCritical(Monster, Hero)"/>
        /// </summary>
        public override void doCritical(Monster monster = null, Hero hero = null)
        {
            if (monster == null)
            {
                Logger.printMsgSystem("There is no Monster to attack.");
                return;
            }
            // subscribe.
            monster.MonsterHit += this.prepToFight;
            Logger.printMsgSystem(String.Format("A swordsman {0} did a critical damage to {1}!", this.Name, monster.getName()));
            int criticalDamageToDeal = (int)(this.Damage * this.CriticalChance) + this.Damage;
            monster.getDamage(criticalDamageToDeal, monster, this);
            // unsubscribe. Reason why to clear subscribed reaction from a monster here: it is a protected member.
            monster.MonsterHit -= this.prepToFight;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.die()"/>
        /// </summary>
        public override void die()
        {
            Logger.printMsgGame(String.Format("The swordsman {0} died bravely.", this.Name));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.beforeDie()"/>
        /// </summary>
        public override void beforeDie()
        {
            // todo: real action, when the SwordsMan is about to die.
            Logger.printMsgGame(String.Format("A swordsman {0} is about to die!", this.Name));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.prepToFight()"/>
        /// </summary>
        protected override void prepToFight()
        {
            Logger.printMsgPlayer(String.Format("Swordsman is ready to fight!"));
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                this.BackPack = null;
                this.HeroPath = null;
                this.Name = String.Empty;
                this.PosX = 0;
                this.PosY = 0;
                this.Health = 0;
                this.Damage = 0;
                this.CriticalChance = 0;
            }
        }

        public override string ToString()
        {
            return String.Format("Hero {0}. Has {1} items in backpack. Damage: {2}. Critical damage: {3:.2}.", this.Name, this.BackPack.getSize(), this.Damage, this.CriticalChance);
        }
    }
}
