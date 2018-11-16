using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to represent all the items, a Hero can handle in his backpack.</para>
    /// <para>All the items are public and static. They are also readonly and already implemented.</para>
    /// <para>User can create only one instance of this class, due to it architecture.</para>
    /// </summary>
    public class ItemsShop
    {
        /// <summary>
        /// <para>List of strings to contain all items in the shop</para>
        /// </summary>
        private string[] items = {
            "magic_sword", "item1", "item2", "item3", "item4", "item5"
        };
        /// <summary>
        /// <para>User can access a list, only if a password is set.</para>
        /// </summary>
        public string[] Items
        {
            get
            {
                if (accessCode == 12345)
                {
                    return items;
                }
                return (new string[0]);
            }
        }

        /// <summary>
        /// <para>Access code for the shop items strings list.</para>
        /// </summary>
        private static int accessCode;
        public static int AccessCode
        {
            set
            {
                if (value == 12345)
                {
                    Logger.printMsgSystem("Access pass is set");
                    accessCode = value;
                }
                else
                {
                    accessCode = 0;
                }
            }
        }

        /// <summary>
        /// <para>Instance of ItemsShop class.</para>
        /// <para>Only one instance of ItemsShop can be created.</para>
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
        /// This class forbids directly creating instance.
        /// </summary>
        private ItemsShop() { }
    }
}
