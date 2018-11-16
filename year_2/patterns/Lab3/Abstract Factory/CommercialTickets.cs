using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    public class CommercialSeatTicket : SeatTicket
    {
        public CommercialSeatTicket(int price, String color, int seatNum, int seatRow)
        {
            this.price = price;
            this.description = "Seat ticket from SuperFactoryINC";
            this.color = color;
            this.seatNum = seatNum;
            this.seatRow = seatRow;
    }

        public override String perkFrommanufacturer()
        {
            return "You get a free sandwich!";
        }
    }

    public class CommercialStandingTicket : StandingTicket
    {
        public CommercialStandingTicket(int price, String color, int zone)
        {
            this.price = price;
            this.description = "Seat ticket from SuperFactoryINC";
            this.color = color;
            this.zone = zone;
        }

        public override String perkFrommanufacturer()
        {
            return "You get a free cola!";
        }
    }

    public class CommercialSpecialTicket : SpecialTicket
    {
        public CommercialSpecialTicket(int price, String color, int seatNum)
        {
            this.price = price;
            this.description = "Seat ticket from SuperFactoryINC";
            this.color = color;
            this.seatNum = seatNum;
        }

        public override String perkFrommanufacturer()
        {
            return "You get a free champagne!";
        }
    }

}
