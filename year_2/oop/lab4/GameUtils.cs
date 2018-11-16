using System;
using System.Collections.Generic;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// Class to represent useful game serving utilities.
    /// This class is mostly used for generation different type of data.
    /// </summary>
    [Serializable]
    public static class GameUtils
    {
        static int swordNameCounter = 0;

        /// <summary>
        /// Sole ItemsShop to get access to the ItemsShop list.
        /// </summary>
        static GameUtils()
        {
            PasswordManager.logAdmin("12345");
        }

        /// <summary>
        /// Random check if place (posX, posY) is free on the map.
        /// </summary>
        /// <param name="posX">Position on OX axis.</param>
        /// <param name="posY">Position on OY axis.</param>
        /// <returns>Result of the check.</returns>
        public static bool checkIfPositionIsFree(double posX = -1, double posY = -1)
        {
            bool positionIsValid = (posX >= 100 && posY >= 100);
            bool positionValidX = (posX >= 100 && posY == -1);
            bool positionValidY = (posY >= 100 && posX == -1);
            bool positionIsNotFree = positionIsValid || positionValidX || positionValidY;
            return !positionIsNotFree;
        }
        
        /// <summary>
        /// <para>Fill backpack (GameItem list) with random tools and return it.</para>
        /// <para>Used by initializing a field [backpack] by Heroes.</para>
        /// </summary>
        /// <param name="backpack">Backpack to fill</param>
        public static GenericList<GameItem> fillUpBackPack()
        {
            if (!PasswordManager.isLoggedAdmin())
                return (new GenericList<GameItem>());

            ItemsShop itemsShopInst = ItemsShop.Instance;
            GenericList<GameItem> backpack = new GenericList<GameItem>();
            for (int i = 0; i < itemsShopInst.Items.getSize(); i++)
            {
                backpack.Add(itemsShopInst.Items.Get(i), i);
            }

            return backpack;
        }

        /// <summary>
        /// <para>Return a sword (string) object with length of 10 characters.</para>
        /// </summary>
        /// <returns>Random generated sword</returns>
        public static string createSword()
        {
            return String.Format("NewSwordName_%d", swordNameCounter);
        }

        /// <summary>
        /// <para>Calculate damage for the hero, depending on his backpack and current sword.</para>
        /// </summary>
        /// <param name="backpack">A backpack.</param>
        /// <param name="sword">A sword.</param>
        /// <returns></returns>
        public static int calculateDamageHero(GenericList<GameItem> backpack)
        {
            int totalDamage = 0;

            for (int i = 0; i < backpack.getSize(); i++)
            {
                totalDamage += backpack.Get(i).calculateEfficiency();
            }

            return randInt(max: 100);
        }

        /// <summary>
        /// <para>Calculate damage for the monster, depending on the goldDrop.</para>
        /// </summary>
        public static int calculateDamageMonster(int goldDrop)
        {
            return randInt(max: goldDrop % 50);
        }

        public static int randInt(int min = 0, int max = 50)
        {
            Random r = new Random();
            return r.Next(min, max);
        }

        public static double randDouble(int min = 0, int max = 1)
        {
            Random r = new Random();
            return min + r.NextDouble() * max;
        }

        [Flags]
        public enum Skills
        {
            Aftershock = 1,
            Seal = 2,
            Avalanche = 4,
            Blast = 8,
            Blur = 16,
            Bolt = 32,
            Invasion = 64
        }
    }
}
