using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to represent useful game utilities.</para>
    /// <para>This class mostly used for generation different type of data.</para>
    /// </summary>
    public static class GameUtils
    {
        /// <summary>
        /// <para>Sole ItemsShop to get access to the ItemsShop list.</para>
        /// </summary>
        private readonly static ItemsShop itemsShopInst;
        static GameUtils()
        {
            ItemsShop.AccessCode = 12345;
            itemsShopInst = ItemsShop.Instance;
        }

        /// <summary>
        /// <para>Random check if place (posX, posY) is free on the map.</para>
        /// </summary>
        /// <param name="posX">Position on OX axis.</param>
        /// <param name="posY">Position on OY axis.</param>
        /// <returns>Result of the check.</returns>
        public static bool checkIfPositionIsFree(double posX = -1, double posY = -1)
        {
            if ((posX >= 100 && posY == -1) ||
                (posY >= 100 && posX == -1) ||
                (posX >= 100 && posY >= 100))
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// <para>Fill backpack (string array) with random tools.</para>
        /// </summary>
        /// <param name="backpack">Backpack to fill</param>
        public static string[] createBackPack()
        {
            string[] backpack = new string[itemsShopInst.Items.Length - 1];
            for (int i = 1; i < backpack.Length; i++)
            {
                backpack[i] = itemsShopInst.Items[i];
            }
            return backpack;
        }

        /// <summary>
        /// <para>Return a sword (string) object with length of 10 characters.</para>
        /// </summary>
        /// <returns>Random generated sword</returns>
        public static string createSword()
        {
            return itemsShopInst.Items[0];
        }

        /// <summary>
        /// <para>Calculate damage for the hero, depending on his backpack and current sword.</para>
        /// </summary>
        /// <param name="backpack">A backpack.</param>
        /// <param name="sword">A sword.</param>
        /// <returns></returns>
        public static int calculateDamageHero(string[] backpack, string sword)
        {
            Random r = new Random();
            return r.Next(50);
        }

        /// <summary>
        /// <para>Calculate damage for the monster, depending on the goldDrop.</para>
        /// </summary>
        /// <param name="goldDrop">Gold dropped from the Monster.</param>
        /// <returns></returns>
        public static int calculateDamageMonster(int goldDrop)
        {
            Random r = new Random();
            return r.Next(50);
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
    }
}
