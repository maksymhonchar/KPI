using System.Collections.Generic;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// Class to represent all items, which a Hero can handle in his backpack.</para>
    /// <para>All the items are public and static. They are also readonly and already implemented.</para>
    /// <para>User can create only one instance of this class, due to it architecture.</para>
    /// </summary>
    public class ItemsShop
    {
        /// <summary>
        /// This class forbids creating instance directly.
        /// </summary>
        private ItemsShop() { }

        /// <summary>
        /// Instance of ItemsShop class.
        /// Only one instance of ItemsShop can be created.
        /// </summary>
        private static ItemsShop instance;
        public static ItemsShop Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new ItemsShop();
                }
                return instance;
            }
        }

        /// <summary>
        /// Create and fill an instance of a backpack.
        /// </summary>
        /// <returns></returns>
        private static GenericList<GameItem> defineBackPack()
        {
            if (!PasswordManager.isLoggedAdmin())
                return (new GenericList<GameItem>());

            GenericList<GameItem> backpack = new GenericList<GameItem>();
            backpack.addFirst(new Sword("magic_sword_1", 100, 50));
            backpack.addFirst(new Sword("magic_sword_2", 200, 60));
            backpack.addFirst(new Sword("magic_sword_3", 300, 70));
            backpack.addFirst(new Shield("mega_shield_1", 50, 100));
            backpack.addFirst(new Shield("mega_shield_2", 60, 200));
            backpack.addFirst(new Shield("mega_shield_3", 70, 300));

            return backpack;
        }

        /// <summary>
        /// User can access a list, only if a password is set.
        /// </summary>
        private GenericList<GameItem> items = defineBackPack();
        public GenericList<GameItem> Items
        {
            get
            {
                if (PasswordManager.isLoggedAdmin())
                {
                    return items;
                }
                return null;
            }
        }
    }
}
