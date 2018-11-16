using System;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// <para>Class to represent a weak knight.</para>
    /// <para>WeakKnight has only 1 damage.</para>
    /// <para>WeakKnight cannot do a critical hit. Instead Hero.doCritical() will be invoked.</para>
    /// </summary>
    [Serializable]
    public class WeakKnight : Hero
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
            // todo: real action, when the SwordsMan dies.
            Logger.printMsgGame(String.Format("The WeakKnight {0} died.", this.Name));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.beforeDie()"/>
        /// </summary>
        public override void beforeDie()
        {
            // todo: real action, when the SwordsMan is about to die.
            Logger.printMsgGame(String.Format("I am about to die, my king...", this.Name));
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.prepToFight()"/>
        /// </summary>
        protected override void prepToFight()
        {
            Logger.printMsgPlayer("A WeakKnight is ready to fight! God bless him.");
        }

        public override string ToString()
        {
            return String.Format("Weak Knight {0} ready!", this.Name);
        }
    }
}
