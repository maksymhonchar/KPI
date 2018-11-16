using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab4_Honchar_Maxim_KP_51
{
    class DiscountCardContext
    {
        private CardDiscountState currentState;

        FivePercentDiscountState fivePercentCard = new FivePercentDiscountState();
        TenPercentDiscountState tenPercentCard = new TenPercentDiscountState();
        FifteenDiscountState fifteenPercentCard = new FifteenDiscountState();

        public DiscountCardContext()
        {
            // Initialize to 5% card as initial state.
            currentState = fivePercentCard;
        }

        private void CheckForNextDiscountState()
        {
            if (currentState == fivePercentCard && currentState.payedInTotal >= 5000)
            {
                tenPercentCard.payedInTotal = currentState.payedInTotal;
                currentState = tenPercentCard;
                Console.WriteLine("Your card discount value has been increased to 10%.");
            }
            else if (currentState == tenPercentCard && currentState.payedInTotal >= 10000)
            {
                fifteenPercentCard.payedInTotal = currentState.payedInTotal;
                currentState = fifteenPercentCard;
                Console.WriteLine("Your card discount value has been increased to 15%.");
            }
        }

        public void Pay(int price)
        {
            currentState.Pay(price);
            CheckForNextDiscountState();
        }

        public override string ToString()
        {
            return currentState.ToString();
        }
    }
}
