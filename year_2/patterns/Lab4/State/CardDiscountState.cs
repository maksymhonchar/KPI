using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab4_Honchar_Maxim_KP_51
{
    abstract class CardDiscountState
    {
        public int discountPercent;
        public int payedInTotal = 0;

        // Return payed amount regarding to discount value.
        public virtual void Pay(int amount)
        {
            payedInTotal += amount;
            Console.WriteLine(
                "You get a {0}% discount and get {1} UAH discount from {2} UAH payed.", 
                discountPercent, amount * discountPercent / 100, amount
            );
        }

        public override string ToString()
        {
            return String.Format("{0}% discount card. Payed: {1}", discountPercent, payedInTotal);
        }
    }

    class FivePercentDiscountState : CardDiscountState
    {
        public FivePercentDiscountState()
        {
            discountPercent = 5;
        }

        public override void Pay(int amount)
        {
            base.Pay(amount);
            Console.WriteLine("As 5% discount card owner you get nothing additional from our shop. Buy more to get more!");
        }
    }

    class TenPercentDiscountState : CardDiscountState
    {
        public TenPercentDiscountState()
        {
            discountPercent = 10;
        }

        public override void Pay(int amount)
        {
            base.Pay(amount);
            Console.WriteLine("As 10% discount card owner you get a handshake from our manager! Buy more to get more!");
        }
    }

    class FifteenDiscountState : CardDiscountState
    {
        public FifteenDiscountState()
        {
            discountPercent = 15;
        }

        public override void Pay(int amount)
        {
            base.Pay(amount);
            Console.WriteLine("As 15% discount card owner you get a cup of coffee from our shop!");
        }
    }
}
