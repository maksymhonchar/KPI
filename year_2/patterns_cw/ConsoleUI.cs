using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    static class ConsoleUI
    {
        private static Shop _shopInst;
        private static Customer _custInst;

        private static int _currentTime;
        
        public static void SetMainInstances(Shop shopInst, Customer custInst)
        {
            _shopInst = shopInst;
            _custInst = custInst;
        }

        public static void MainLoop()
        {
            PrintMainShowcase();

            // Add items into your cart.
            while (true)
            {
                Product productToAddToCart = null;

                // Get a category.
                Console.WriteLine("Choose category.");
                char category = Console.ReadLine().ToLower().ToCharArray()[0];
                while (category != 'w' && category != 'f' && category != 'd' && category != 't')
                {
                    if (category == '>')
                    {
                        break;
                    }
                    RestartScreen();
                    Console.WriteLine("Choose category. Please, choose one from above.");
                    category = Console.ReadLine().ToLower().ToCharArray()[0];
                }
                if (category == '>')
                {
                    break;
                }

                RestartScreen();

                // Choose a product.
                Console.WriteLine("Choose a product.");
                char productId = Console.ReadLine().ToCharArray()[0];
                while (productId != '0' && productId != '1')
                {
                    if (productId == '>')
                    {
                        break;
                    }
                    RestartScreen();
                    Console.WriteLine("Choose a product. Please, choose one from above.");
                    category = Console.ReadLine().ToCharArray()[0];
                }
                if (productId == '>')
                {
                    break;
                }

                RestartScreen();

                // Choose an item to your cart.
                switch (category)
                {
                    case 'w':
                        switch (productId)
                        {
                            case '0':
                                productToAddToCart = _shopInst.mainShowCase.washingMachineStand[0];
                                break;
                            case '1':
                                productToAddToCart = _shopInst.mainShowCase.washingMachineStand[1];
                                break;
                        }
                        break;
                    case 'f':
                        switch (productId)
                        {
                            case '0':
                                productToAddToCart = _shopInst.mainShowCase.fridgeStand[0];
                                break;
                            case '1':
                                productToAddToCart = _shopInst.mainShowCase.fridgeStand[1];
                                break;
                        }
                        break;
                    case 'd':
                        switch (productId)
                        {
                            case '0':
                                productToAddToCart = _shopInst.mainShowCase.dishWasherStand[0];
                                break;
                            case '1':
                                productToAddToCart = _shopInst.mainShowCase.dishWasherStand[1];
                                break;
                        }
                        break;
                    case 't':
                        switch (productId)
                        {
                            case '0':
                                productToAddToCart = _shopInst.mainShowCase.tvSetStand[0];
                                break;
                            case '1':
                                productToAddToCart = _shopInst.mainShowCase.tvSetStand[1];
                                break;
                        }
                        break;
                }
                // Add an item.
                _custInst.AddToCart(productToAddToCart);

                // Restart a screen at the end.
                RestartScreen();
            }

            RestartScreen_2();

            // Buy items.
            _shopInst.WorkAtCashRegister(_currentTime, _custInst);

            // End of the buying routine.
            Console.WriteLine("End of the buying cycle.");
        }

        #region Console_UI_1
        public static void PrintMainShowcase()
        {
            // todo: current time for shop.WorkAtCashRegister
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("Items in shop:");
            _shopInst.PrintShowcaseItems();
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("Current time: {0}", InUITime());
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("Press '>' and 'enter' to pay for products in the cart");
            Console.WriteLine("----------------------------------------------------------");
        }

        public static void RestartScreen()
        {
            Console.Clear();
            PrintMainShowcase();
        }

        private static int InUITime()
        {
            return (_currentTime++ % 24) + 1;
        }
        #endregion

        #region Console_UI_2
        public static void PrintCustomerCart()
        {
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("{0}. {1}UAH. Total bought: {2}UAH. Discount: {3}%", 
                _custInst.Name, _custInst.Money, _custInst.boughtInTotal, _custInst.discountCardValue);
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("{0} cart:", _custInst.Name);
            foreach (Product item in _custInst.cart)
            {
                Console.WriteLine(item);
            }
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("Current time: {0}", InUITime());
            Console.WriteLine("----------------------------------------------------------");
        }

        public static void RestartScreen_2()
        {
            Console.Clear();
            PrintCustomerCart();
        }

        #endregion
    }
}