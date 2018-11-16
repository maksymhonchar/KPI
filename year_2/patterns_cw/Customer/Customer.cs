using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class Customer
    {
        private CustomerPayment paymentType;

        public List<Product> cart;
        public String Name { get; set; }
        public String Address { get; set; }
        public uint Money { get; set; }
        public int discountCardValue;
        public uint boughtInTotal;

        public Customer(String name, uint money)
        {
            this.paymentType = new CustomerPayment(new CashPayment());
            this.cart = new List<Product>();
            this.Name = name;
            this.Money = money;
            this.boughtInTotal = 0;
        }

        public void SetUpCustomer(String address, int discCardValue = 0)
        {
            this.Address = address;
            this.discountCardValue = discCardValue;

            if (discountCardValue != 0)
            {
                this.paymentType = new CustomerPayment(new CardPayment());
            }
            else if (discountCardValue == 0 && this.Money > 0)
            {
                this.paymentType = new CustomerPayment(new CashPayment());
            }
        }

        public void AddToCart(Product product)
        {
            this.cart.Add(product);
            Console.WriteLine("A {0} added to your cart.", product.name);
        }

        public void PayForProduct(Product productToBuy, uint discountValue)
        {
            uint toPayForProduct = this.paymentType.PayForProduct(productToBuy.price - discountValue);
            
            if (toPayForProduct <= this.Money)
            {
                this.Money -= toPayForProduct;
                this.boughtInTotal += toPayForProduct;
                this.cart.Remove(productToBuy);
                Console.WriteLine("Bought a {0} for {1}.", productToBuy.name, toPayForProduct);
            }
            else
            {
                Console.WriteLine("Sorry, not enough for {0}", productToBuy.name);
            }
        }
    }
}
