using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    abstract class DeliveryService
    {
        public abstract void DeliverProduct(Customer customer, Product product);
        public abstract void ShowDeliveryInfo();
    }

    // "Default" delivery implementation.
    class BasicDeliveryService : DeliveryService
    {
        public override void DeliverProduct(Customer customer, Product product)
        {
            Console.WriteLine("Trying to send {0} to {1}.", product.name, customer.Name);
            this.ShowDeliveryInfo();
        }

        public override void ShowDeliveryInfo()
        {
        }
    }
}
