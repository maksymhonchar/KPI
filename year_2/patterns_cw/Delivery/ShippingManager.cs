using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    public static class ShippingTypes
    {
        public const String ByFoot = "f";
        public const String ByTrain = "t";
        public const String ByAir = "a";
        public const String ByAirAndTrain = "at";
        public const String ByAirAndFoot = "af";
        public const String ByAirAndTrainAndFoot = "atf";
    }

    class ShippingManager
    {
        private DeliveryService _deliveryService;

        private Customer _customerTmpObj;
        private Product _productTmpObj;

        private Decorator footShipping;
        private Decorator trainShipping;
        private Decorator airShipping;

        public ShippingManager()
        {
            _deliveryService = new BasicDeliveryService();

            footShipping = new ByFootDelivery();
            trainShipping = new ByTrainDelivery();
            airShipping = new ByAirDelivery();
        }

        public void ShipProduct(Product product, Customer customer, String shippingOption)
        {
            _productTmpObj = product;
            _customerTmpObj = customer;

            switch (shippingOption)
            {
                case ShippingTypes.ByFoot:
                    ByFootShipping();
                    break;
                case ShippingTypes.ByTrain:
                    TrainShipping();
                    break;
                case ShippingTypes.ByAir:
                    AirShipping();
                    break;
                case ShippingTypes.ByAirAndTrain:
                    AirAndTrainShipping();
                    break;
                case ShippingTypes.ByAirAndFoot:
                    AirAndByFootShipping();
                    break;
                case ShippingTypes.ByAirAndTrainAndFoot:
                    AirAndByTrainAndByFootShipping();
                    break;
                default:
                    Console.WriteLine("No shipping chosen.");
                    break;
            }
        }

        private void AirShipping()
        {
            airShipping.AddShippingRoute(_deliveryService);
            ShowDeliveryTracking(airShipping, _productTmpObj, _customerTmpObj);
        }

        private void TrainShipping()
        {
            trainShipping.AddShippingRoute(_deliveryService);
            ShowDeliveryTracking(trainShipping, _productTmpObj, _customerTmpObj);
        }

        private void ByFootShipping()
        {
            footShipping.AddShippingRoute(_deliveryService);
            ShowDeliveryTracking(footShipping, _productTmpObj, _customerTmpObj);
        }

        private void AirAndTrainShipping()
        {
            trainShipping.AddShippingRoute(_deliveryService);
            airShipping.AddShippingRoute(trainShipping);
            ShowDeliveryTracking(airShipping, _productTmpObj, _customerTmpObj);
        }

        private void AirAndByFootShipping()
        {
            footShipping.AddShippingRoute(_deliveryService);
            airShipping.AddShippingRoute(footShipping);
            ShowDeliveryTracking(airShipping, _productTmpObj, _customerTmpObj);
        }

        private void AirAndByTrainAndByFootShipping()
        {
            footShipping.AddShippingRoute(_deliveryService);
            trainShipping.AddShippingRoute(footShipping);
            airShipping.AddShippingRoute(trainShipping);
            ShowDeliveryTracking(airShipping, _productTmpObj, _customerTmpObj);
        }

        private void ShowDeliveryTracking(Decorator lastDecoratorInChain, Product product, Customer customer)
        {
            lastDecoratorInChain.DeliverProduct(customer, product);
            Console.WriteLine("Tracking delivery of {0} to {1}:", product.name, customer.Name);
            lastDecoratorInChain.ShowDeliveryInfo();
        }
    }
}
