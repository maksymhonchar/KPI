using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class Program
    {
        static void Main(string[] args)
        {
            Shop shop = new Shop();
            Customer customer = new Customer("Maxim", 100000);
            customer.SetUpCustomer("KPI");  // lives in KPI, no discount value.

            ConsoleUI.SetMainInstances(shop, customer);

            ConsoleUI.MainLoop();

            Console.ReadKey();
            Console.ReadKey();
            Console.ReadKey();
            Console.ReadKey();
        }
    }
}
