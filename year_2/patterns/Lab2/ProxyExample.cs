using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab2_Honchar_Maxim_KP_51
{
    class BankUser
    {
        public string name;
        public bool isConnectedToService;

        public BankUser(string name)
        {
            this.name = name;
            this.isConnectedToService = false;
        }
    }

    // Interface for a Bank.
    abstract class AbstractBank
    {
        public abstract void PrintDocument(BankUser client);
        public abstract void ConnectToService(BankUser client);
    }

    // A real subject.
    class Bank : AbstractBank
    {
        public override void PrintDocument(BankUser client)
        {
            Console.WriteLine("Please, take your document, {0}.", client.name);
        }

        public override void ConnectToService(BankUser client)
        {
            client.isConnectedToService = true;
        }
    }

    // A proxy class.
    class BankSecurityDepartment : AbstractBank
    {
        Bank bank = new Bank();

        public override void PrintDocument(BankUser client)
        {
            if (client.isConnectedToService)
            {
                // Allow a user to process his document request.
                bank.PrintDocument(client);
            }
            else
            {
                // Prevent the user from creating a request until the one is not connected to service.
                Console.WriteLine("Sorry, {0}, we are not able to process your " +
                    "document request. Please, connect to our service first.", client.name);
            }
        }

        public override void ConnectToService(BankUser client)
        {
            Console.WriteLine("Please, {0}, follow me sir.", client.name);
            bank.ConnectToService(client);
        }
    }
}
