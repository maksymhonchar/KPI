using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    public abstract class Ticket
    {
        public String description;
        public String color;
        public int price;

        public virtual String perkFrommanufacturer()
        {
            return "No additional perk.";
        }

        public override string ToString()
        {
            return String.Format("{0}. Price: {1}. Color: {2}", description, price, color);
        }
    }

    public interface ISeatable
    {
        String printSeatInfo();
    }

    public abstract class SeatTicket : Ticket, ISeatable
    {
        public int seatRow;
        public int seatNum;

        public String printSeatInfo()
        {
            return String.Format("Row:{0}; Num:{1}", seatRow, seatNum);
        }
    }

    public abstract class StandingTicket : Ticket
    {
        public int zone;
    }

    public abstract class SpecialTicket : Ticket, ISeatable
    {
        public const int seatRow = 1;
        public int seatNum;
        public String specialDescription;

        public String printSeatInfo()
        {
            return String.Format("Row:{0}; Num:{1}", seatRow, seatNum);
        }
    }
}
