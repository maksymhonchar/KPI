using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class Shop
    {
        public Showcase mainShowCase;
        private CashRegisterSeller _cashRegisterSeller;

        public Shop()
        {
            mainShowCase = Showcase.Instance();
            _cashRegisterSeller = new CashRegisterSeller();
        }

        public void WorkAtCashRegister(int currentTime, Customer customer)
        {
            _cashRegisterSeller.WorkWithClientAtTime(currentTime, customer);
        }

        public void PrintShowcaseItems()
        {
            int ctr = 0;
            Console.WriteLine("[W]ashing machines:");
            foreach (Product item in mainShowCase.washingMachineStand)
            {
                Console.WriteLine(String.Format("\t[{0}] {1};", ctr++.ToString(), item.ToString()));
            }
            ctr = 0;

            Console.WriteLine("[F]ridges:");
            foreach (Product item in mainShowCase.fridgeStand)
            {
                Console.WriteLine(String.Format("\t[{0}] {1};", ctr++.ToString(), item.ToString()));
            }
            ctr = 0;

            Console.WriteLine("[D]ish washers:");
            foreach (Product item in mainShowCase.dishWasherStand)
            {
                Console.WriteLine(String.Format("\t[{0}] {1};", ctr++.ToString(), item.ToString()));
            }
            ctr = 0;

            Console.WriteLine("[T]V sets:");
            foreach (Product item in mainShowCase.tvSetStand)
            {
                Console.WriteLine(String.Format("\t[{0}] {1};", ctr++.ToString(), item.ToString()));
            }
        }
    }
}
