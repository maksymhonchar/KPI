using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    // Implementor for a "bridge" design pattern.
    class CustomerPayment
    {
        ICustomerPayForProduct paymentType;

        public CustomerPayment(ICustomerPayForProduct paymentType)
        {
            this.paymentType = paymentType;
        }

        public void SetPaymentType(ICustomerPayForProduct paymentType)
        {
            if (paymentType == null)
                return;
            this.paymentType = paymentType;
        }

        public uint PayForProduct(uint toPay)
        {
            return this.paymentType.PayForProduct(toPay);
        }
    }

    // Abstraction.
    interface ICustomerPayForProduct
    {
        // return how much payed.
        uint PayForProduct(uint toPay);
    }

    // First concrete abstraction - paying with credit card.
    class CardPayment : ICustomerPayForProduct
    {
        // Get a 10% cashback as a card credit card owner.
        public uint PayForProduct(uint toPay)
        {
            return (uint)(toPay * 0.9);
        }
    }

    // Second concrete abstraction - paying with cash.
    class CashPayment : ICustomerPayForProduct
    {
        // Regular payment without cashback.
        public uint PayForProduct(uint toPay)
        {
            return toPay;
        }
    }
}
