using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    public class StateSeatTicket : SeatTicket
    {
        public StateSeatTicket(int price, String color, int seatNum, int seatRow)
        {
            this.price = price;
            this.description = "Seat ticket from Kyiv state";
            this.color = color;
            this.seatNum = seatNum;
            this.seatRow = seatRow;
        }
    }

    public class StateStandingTicket : StandingTicket
    {
        public StateStandingTicket(int price, String color, int zone)
        {
            this.price = price;
            this.description = "Standing ticket from Kyiv state";
            this.color = color;
            this.zone = zone;
        }
    }

    public class StateSpecialTicket : SpecialTicket
    {
        public StateSpecialTicket(int price, String color, int seatNum)
        {
            this.price = price;
            this.description = "Special ticket from Kyiv state";
            this.color = color;
            this.seatNum = seatNum;
        }
    }

}
