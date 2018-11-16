using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    // The 'AbstractFactory' abstract class to inherit from.
    public abstract class TicketFactory
    {
        public List<String> colors;
        public String content;
        protected Random rand;

        public abstract SeatTicket CreateSeatTicket();
        public abstract StandingTicket CreateStandingTicket();
        public abstract SpecialTicket CreateSpecialTicket();
    }

    public class StateFactory : TicketFactory
    {
        public StateFactory()
        {
            this.colors = new List<string> { "White", "Black" };
            this.rand = new Random();
        }

        public override SeatTicket CreateSeatTicket()
        {
            return new StateSeatTicket(rand.Next(100), this.colors[rand.Next(2)], rand.Next(50), rand.Next(50));
        }

        public override StandingTicket CreateStandingTicket()
        {
            return new StateStandingTicket(rand.Next(100), this.colors[rand.Next(2)], rand.Next(10));
        }

        public override SpecialTicket CreateSpecialTicket()
        {
            return new StateSpecialTicket(rand.Next(100), this.colors[rand.Next(2)], rand.Next(20, 30));
        }
    }

    public class CommercialFactory : TicketFactory
    {
        public CommercialFactory()
        {
            this.colors = new List<string> { "Red", "Green", "Blue", "White", "Black" };
            this.rand = new Random();
        }

        public override SeatTicket CreateSeatTicket()
        {
            return new CommercialSeatTicket(rand.Next(100, 500), this.colors[rand.Next(5)], rand.Next(50), rand.Next(50));
        }

        public override StandingTicket CreateStandingTicket()
        {
            return new CommercialStandingTicket(rand.Next(100, 500), this.colors[rand.Next(5)], rand.Next(10));
        }

        public override SpecialTicket CreateSpecialTicket()
        {
            return new CommercialSpecialTicket(rand.Next(100, 500), this.colors[rand.Next(5)], rand.Next(20, 30));
        }

    }

}
