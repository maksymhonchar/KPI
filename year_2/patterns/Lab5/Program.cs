using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab5_Honchar_Maxim_KP_51
{
    class Program
    {
        static void Main(string[] args)
        {
            ChainOfResponsibilityExample();

            Console.WriteLine(Environment.NewLine);

            CommandPatternExample();

            Console.ReadKey();
        }

        private static void ChainOfResponsibilityExample()
        {
            /*
            І зміна – з 6.00 до 15.00, 
            ІІ зміна – з 14.00 до 23.00,
            ІІІ зміна – з 22.00 до 7.00. 
             */

            FactoryExample factory = new FactoryExample();

            Console.WriteLine("Try to give work at 11 AM");
            factory.SetWork(11);

            Console.WriteLine(Environment.NewLine);

            Console.WriteLine("Try to give work at 15 PM");
            factory.SetWork(15);

            Console.WriteLine(Environment.NewLine);

            Console.WriteLine("Try to give work at 5AM");
            factory.SetWork(5);
        }

        private static void CommandPatternExample()
        {
            InfoSystem infoSystem = new InfoSystem();
            String data = String.Empty;

            Console.WriteLine("Add operation:");
            data = infoSystem.Add("This is a new string.");
            Console.WriteLine("\"{0}\"", data);

            Console.WriteLine(Environment.NewLine);

            Console.WriteLine("Delete operation:");
            data = infoSystem.Delete(data);
            Console.WriteLine("\"{0}\"", data);

            Console.WriteLine(Environment.NewLine);

            Console.WriteLine("Edit operation:");
            data = infoSystem.Edit("Edited string for lab5.");
            Console.WriteLine("\"{0}\"", data);
        }
    }
}
