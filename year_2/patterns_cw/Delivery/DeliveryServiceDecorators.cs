using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    // Main abstract decorator class.
    abstract class Decorator : DeliveryService
    {
        protected DeliveryService deliveryService;

        public void AddShippingRoute(DeliveryService service)
        {
            this.deliveryService = service;
        }

        public override void DeliverProduct(Customer customer, Product product)
        {
            if (deliveryService != null)
            {
                deliveryService.DeliverProduct(customer, product);
            }
        }

        public override void ShowDeliveryInfo()
        {
            if (deliveryService != null)
            {
                deliveryService.ShowDeliveryInfo();
            }
        }
    }

    // Example of concrete decorator
    class ByAirDelivery : Decorator
    {
        public override void DeliverProduct(Customer customer, Product product)
        {
            Console.WriteLine("{0} air delivery order was sent to {1} by address {2}.", product.name, customer.Name, customer.Address);
            base.DeliverProduct(customer, product);
        }

        public override void ShowDeliveryInfo()
        {
            Console.WriteLine("Shipping by air");
            base.ShowDeliveryInfo();
        }
    }

    class ByTrainDelivery : Decorator
    {
        public override void DeliverProduct(Customer customer, Product product)
        {
            Console.WriteLine("{0} train delivery order was sent to {1} by address {2}.", product.name, customer.Name, customer.Address);
            base.DeliverProduct(customer, product);
        }

        public override void ShowDeliveryInfo()
        {
            Console.WriteLine("Shipping by train");
            base.ShowDeliveryInfo();
        }
    }

    class ByFootDelivery : Decorator
    {
        public override void DeliverProduct(Customer customer, Product product)
        {
            Console.WriteLine("{0} by foot delivery order was sent to {1} by address {2}.", product.name, customer.Name, customer.Address);
            base.DeliverProduct(customer, product);
        }

        public override void ShowDeliveryInfo()
        {
            Console.WriteLine("Shipping by foot");
            base.ShowDeliveryInfo();
        }
    }
}
