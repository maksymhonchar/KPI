using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab2_Honchar_Maxim_KP_51
{
    class Program
    {
        static void Main(string[] args)
        {
            firstTaskDemonstration();

            Console.WriteLine(Environment.NewLine);

            secondTaskDemonstration();

            Console.WriteLine("End of the program");
            Console.ReadKey();
        }

        static void firstTaskDemonstration()
        {
            // Create some instances of Bank security and Users.
            BankSecurityDepartment mainSecurityDepartent = new BankSecurityDepartment();
            BankUser firstClient = new BankUser("Alexei");
            BankUser secondClient = new BankUser("Mihail");

            // Try to get a document for both of them.
            mainSecurityDepartent.PrintDocument(firstClient);
            mainSecurityDepartent.PrintDocument(secondClient);

            // Allow the first one to process a document.
            mainSecurityDepartent.ConnectToService(firstClient);

            // Try to get a doc for a first one again.
            mainSecurityDepartent.PrintDocument(firstClient);
        }

        static void secondTaskDemonstration()
        {
            // Old-style signup.
            OldishCompany oldComp = new OldishCompany();
            oldComp.SignUp();
            oldComp.Display();

            Console.WriteLine(Environment.NewLine);

            // New-style signup.
            NewishCompany newComp = new NewishCompany();
            newComp.SignUp();
            newComp.Display();
        }
    }
}
