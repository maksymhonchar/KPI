using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class CashRegisterSeller
    {
        private Shift _morningShift;        // from 06:00-13:00
        private Shift _dayShift;            // from 13:00-20:00
        private Shift _firstNightShift;     // from 20:00-00:00
        private Shift _secondNightShift;    // from 00:00-06:00

        private DiscountCardCheckerManager _discountCardChecker;
        private ProductDocumentationFormer _productDocsFormer;
        private ShippingManager _shippingManager;

        public CashRegisterSeller()
        {
            _morningShift = new SellerShift(6, 13, "Natasha");
            _dayShift = new SellerShift(13, 20, "Nikita");
            _firstNightShift = new SellerShift(20, 24, "Karina");
            _secondNightShift = new SellerShift(0, 6, "Wadim");
            this.SetSchedule();

            _discountCardChecker = new DiscountCardCheckerManager();
            _productDocsFormer = new ProductDocumentationFormer();
            _shippingManager = new ShippingManager();
        }

        public void WorkWithClientAtTime(int time, Customer customer)
        {
            if (time < 0 || time > 24)
            {
                Console.WriteLine("Wrong time argument");
                return;
            }

            // try to give call a certain sellers shift.
            // starts from _secondNight shift, because this is a start of the day.
            Console.WriteLine(_secondNightShift.Work(time));

            // get money from a customer for each product in his cart.
            Console.WriteLine("");

            List<Product> customCartCopy = customer.cart.ToList();
            foreach (Product itemInCart in customCartCopy)
            {
                Console.WriteLine("{0} is on the cash register. Price: {1}", itemInCart.name, itemInCart.price);

                // Try to get a discount.
                uint discountValue = (_discountCardChecker.MakeDiscount(customer, itemInCart));

                // Pay for an item from cart.
                customer.PayForProduct(itemInCart, discountValue);

                // Form documents package.
                _productDocsFormer.FormDocumentationPackage(itemInCart);

                Console.WriteLine("");
            }

            // Select a shipping for all items.
            Console.WriteLine("---------------------------------------------------------");

            #region Shipping_User_Input
            Console.WriteLine("Would you like to order a shipping?");
            Console.WriteLine(String.Format(
                "[f] - by foot\t[t] - by train\t[a] - by air\n\r[at] - by air and train\n[af] - by air and foot\n[atf] - by air, train and by foot.\n[anything else] - decline.")
            );
            char[] category = Console.ReadLine().ToLower().ToCharArray();
            String categoryInString = new string(category);
            Console.WriteLine(categoryInString);
            if (categoryInString != "f" && 
                categoryInString != "t" &&
                categoryInString != "a" &&
                categoryInString != "at" &&
                categoryInString != "af" &&
                categoryInString != "atf"
                )
            {
                categoryInString = "none";
            }

            ConsoleUI.RestartScreen_2();
            #endregion

            if (categoryInString != "none")
            {
                foreach (Product itemInCart in customCartCopy)
                {
                    _shippingManager.ShipProduct(itemInCart, customer, categoryInString);
                    Console.WriteLine("");
                }
            }
            else
            {
                Console.WriteLine("No shipping was chosen.");
            }
        }

        private void SetSchedule()
        {
            _morningShift.NextShift = _dayShift;
            _dayShift.NextShift = _firstNightShift;
            _firstNightShift.NextShift = _secondNightShift;
            _secondNightShift.NextShift = _morningShift;
        }
    }
}
