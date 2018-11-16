using System;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// <para>Class to represent a casual monster.</para>
    /// <para>Casual Monster has twice less damage, than default Monster.</para>
    /// <para>Casual Monster cannot do a critical hit. Instead Monster.doCritical() will be invoked.</para>
    /// </summary>
    [Serializable]
    public class CasualMonster : Monster
    {
        /// <summary>
        /// <para>Default constructor, that fills only Damage field.</para>
        /// </summary>
        public CasualMonster() 
            : base()
        {
            this.Damage = 5;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Monster.prepToFight()"/>
        /// </summary>
        protected override void prepToFight()
        {
            Logger.printMsgPlayer("A casual monster is ready to fight!");
        }

        public override string ToString()
        {
            return String.Format("Arrrgh, I will kill you! By the way, my name is {0}.", this.Name);
        }
    }
}
