using System;

namespace MonstersHeroesEmulator
{
    public abstract class GameItem : IGameItem
    {
        private string name;
        public string Name
        {
            get
            {
                return this.name;
            }
            set
            {
                this.name = value;
            }
        }

        protected int durability;
        protected double strength;
        protected double agility;
        protected double intelligence;
        protected int cost;

        /// <summary>
        /// <para>Basic constructor with default name for an item.</para>
        /// </summary>
        protected GameItem(string name)
        {
            this.durability = 100;
            this.strength = 0;
            this.agility = 0;
            this.intelligence = 0;
            this.cost = 0;
            this.Name = name;
        }

        /// <summary>
        /// <para>Calculate efficiency of the game item with formula [strength+agility+intelligence]</para>
        /// </summary>
        public abstract int calculateEfficiency();

        /// <summary>
        /// <para>Increase durability of the game item - increase his strength, agility and intelligence.</para>
        /// </summary>
        /// <param name="value">Heal made to the item</param>
        public abstract void increaseDurability(int value);

        /// <summary>
        /// <para>Decrease durability of the game item - decrease his strength, agility and intelligence.</para>
        /// </summary>
        /// <param name="value">Damage, dealed to the item.</param>
        public abstract void decreaseDurability(int value);
        
        public override string ToString()
        {
            return String.Format("GameItem {0}. Cost: {1}.", this.name, this.cost);
        }
    }
}
