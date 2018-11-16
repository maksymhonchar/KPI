using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    // The 'Client' class.
    class TicketClient
    {
        private SeatTicket _seatTicket;
        private StandingTicket _standingTicket;
        private SpecialTicket _specialTicket;

        public void printTickets(TicketFactory factory)
        {
            _seatTicket = factory.CreateSeatTicket();
            _standingTicket = factory.CreateStandingTicket();
            _specialTicket = factory.CreateSpecialTicket();
        }

        public void printPrintedTicketsInfo()
        {
            Console.WriteLine(
                String.Format( "Printed tickets:\n{0}\n{1}\n{2}", 
                _seatTicket.ToString(), _standingTicket.ToString(), _specialTicket.ToString() ) 
            );
        }

        public void printPrintedTicketsPerks()
        {
            Console.WriteLine(
                String.Format( "Seat ticket perk: {0}\nStanding ticket perk: {1}\nSpecial ticket perk: {2}", 
                _seatTicket.perkFrommanufacturer(), 
                _standingTicket.perkFrommanufacturer(), 
                _specialTicket.perkFrommanufacturer() )
            );
        }
    }
}
