using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to represent a weak knight.</para>
    /// <para>WeakKnight has only 1 damage.</para>
    /// <para>WeakKnight cannot do a critical hit. Instead Hero.doCritical() will be invoked.</para>
    /// </summary>
    public class WeakKnight : Hero
    {
        /// <summary>
        /// <para>Default constructor, that fills only Damage field.</para>
        /// </summary>
        public WeakKnight() : base()
        {
            this.Damage = 1;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.dealDamage(Monster, Hero)"/>
        /// </summary>
        public override void dealDamage(Monster monster = null, Hero hero = null)
        {
            this.prepareToFight();
            Logger.printMsgPlayer("Master, I will fight for you! WeakKnight is attacking!");
            monster.getDamage(this.Damage, hero: this);
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.getDamage(int, Monster, Hero)"/>
        /// </summary>
        public override void getDamage(int damage, Monster monster = null, Hero hero = null)
        {
            Logger.printMsgPlayer("Oh no, Weak knight got damaged...");
            this.Health -= damage;
        }

        /// <summary>
        /// <see text="Overridden from " cref="Hero.prepareToFight()"/>
        /// </summary>
        protected override void prepareToFight()
        {
            Logger.printMsgPlayer("A WeakKnight is ready to fight! God bless him.");
        }

        public override string ToString()
        {
            return String.Format("Weak Knight {0} ready!", this.Name);
        }
    }
}
