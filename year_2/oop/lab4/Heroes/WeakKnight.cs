using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// <para>Class to represent a weak knight.</para>
    /// <para>WeakKnight has only 1 damage.</para>
    /// <para>WeakKnight cannot do a critical hit. Instead Hero.doCritical() will be invoked.</para>
    /// </summary>
    [Serializable]
    public class WeakKnight : Hero, IDisposable
    {
        /// <summary>
        /// <para>Default constructor, that fills only Damage field.</para>
        /// </summary>
        public WeakKnight() : base()
        {
            this.Damage = 5;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.die()"/>
        /// </summary>
        public override void die()
        {
            Logger.printMsgGame(String.Format("The WeakKnight {0} died.", this.Name));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.beforeDie()"/>
        /// </summary>
        public override void beforeDie()
        {
            Logger.printMsgGame(String.Format("I am about to die, my king...", this.Name));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.prepToFight()"/>
        /// </summary>
        protected override void prepToFight()
        {
            Logger.printMsgPlayer("A WeakKnight is ready to fight! God bless him.");
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
            }
        }

        public override string ToString()
        {
            return String.Format("Weak Knight {0} ready!", this.Name);
        }
    }
}
