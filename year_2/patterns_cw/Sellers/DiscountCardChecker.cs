using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    enum DiscountCardValues
    {
        NoDiscountCard = 0,
        FivePercentDiscount = 5,
        TenPercentDiscount = 10,
        FifteenPercentDiscount = 15
    }

    // interface for a discount checker.
    abstract class AbstractDiscountChecker
    {
        public abstract uint MakeDiscount(Customer customer, Product product);
        public abstract void GiveDiscountCard(Customer customer);
    }

    // A real discount checker.
    class DiscountCardChecker : AbstractDiscountChecker
    {
        public override uint MakeDiscount(Customer customer, Product product)
        {
            return (uint)(product.price * customer.discountCardValue / 100);
        }

        public override void GiveDiscountCard(Customer customer)
        {
            customer.discountCardValue = (int)DiscountCardValues.FivePercentDiscount;
        }
    }

    // A proxy class.
    class DiscountCardCheckerManager : AbstractDiscountChecker
    {
        DiscountCardChecker cardChecker = new DiscountCardChecker();

        public override uint MakeDiscount(Customer customer, Product product)
        {
            // If a customer does not have a discount card yet.
            if (customer.discountCardValue == (int)DiscountCardValues.NoDiscountCard)
            {
                Console.WriteLine("You just earned a new 5% discount card. Congrats!");
                // Give a new discount card to the customer.
                this.GiveDiscountCard(customer);
                // Get a discount with new discount card value.
                return cardChecker.MakeDiscount(customer, product);
            }
            else // if a customer already has a discount card.
            {
                // try to give a discount card.
                this.GiveDiscountCard(customer);
                return cardChecker.MakeDiscount(customer, product);
            }
        }

        public override void GiveDiscountCard(Customer customer)
        {
            switch (customer.discountCardValue)
            {
                case (int)DiscountCardValues.NoDiscountCard:
                    customer.discountCardValue = (int)DiscountCardValues.FivePercentDiscount;
                    break;

                case (int)DiscountCardValues.FivePercentDiscount:
                    if (customer.boughtInTotal >= 5000)
                    {
                        customer.discountCardValue = (int)DiscountCardValues.TenPercentDiscount;
                        Console.WriteLine("Congrats, have a 10% discount card!");
                    }
                    break;

                case (int)DiscountCardValues.TenPercentDiscount:
                    if (customer.boughtInTotal >= 10000)
                    {
                        customer.discountCardValue = (int)DiscountCardValues.FifteenPercentDiscount;
                        Console.WriteLine("Congrats, have a 15% discount card!");
                    }
                    break;
            }
        }
    }
}
