using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace WPF_HeroesMonsters
{
    [Serializable]
    public class Hero
    {
        // Private fields.
        public string name;
        public int damage;
        public int strength;
        public int evasion;

        // Properties.
        public string Name
        {
            get
            {
                return this.name;
            }
            set
            {
                if (!String.IsNullOrEmpty(value))
                {
                    this.name = value;
                }
            }
        }
        public int Damage
        {
            get
            {
                return this.damage;
            }
            set
            {
                if (value >= 0)
                {
                    this.damage = value;
                }
            }
        }
        public int Strength
        {
            get
            {
                return this.strength;
            }
            set
            {
                if (value >= 0)
                {
                    this.strength = value;
                }
            }
        }
        public int Evasion
        {
            get
            {
                return this.evasion;
            }
            set
            {
                if (value >= 0)
                {
                    this.evasion = value;
                }
            }
        }

        // Constructors.
        public Hero()
        {
            this.Name = "NoName";
            this.Damage = 0;
            this.Strength = 0;
            this.Evasion = 0;
        }

        public Hero(string name) : this()
        {
            this.Name = name;
        }

        public Hero(string name, int damage, int strength, int evasion)
            : this(name)
        {
            this.Damage = damage;
            this.Strength = strength;
            this.Evasion = evasion;
        }
    }


    public class HeroModel : ObservableCollection<Hero>
    {
        private static object _threadLock = new Object();
        private static HeroModel current = null;

        public static HeroModel Current
        {
            get
            {
                lock (_threadLock)
                    if (null == current)
                        current = new HeroModel();
                return current;
            }
        }

        private HeroModel()
        {
            Hero[] heroArr = BinaryToData();
            foreach (Hero heroObj in heroArr)
            {
                Add(heroObj);
            }
        }

        public int getHeroIndex(Hero hero)
        {
            return IndexOf(hero);
        }

        public void removeHero(Hero hero)
        {
            Remove(hero);
        }

        public void addHero(Hero hero, int index)
        {
            Insert(index, hero);
        }

        public void addHero(string name, int damage, int strength, int evasion)
        {
            Hero heroObj = new Hero(name, damage, strength, evasion);
            Add(heroObj);
        }

        public void saveHero()
        {
            DataToBinary(Current.ToArray());
        }

        // Serialization.
        public static void DataToBinary(Hero[] heroArr)
        {
            FileStream fs = new FileStream("swordsman.dat", FileMode.Create);
            BinaryFormatter bf = new BinaryFormatter();
            bf.Serialize(fs, heroArr);
            fs.Close();
        }

        // Deserialization.
        public static Hero[] BinaryToData()
        {
            FileStream fs = new FileStream("swordsman.dat", FileMode.Open);
            BinaryFormatter bf = new BinaryFormatter();
            Hero[] heroBuf = (Hero[])bf.Deserialize(fs);
            fs.Close();

            return heroBuf;
        }
    }
}
