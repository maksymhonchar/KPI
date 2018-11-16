using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    // Abstract handler
    abstract class Shift
    {
        protected int _startWrkTime;
        protected int _endWrkTime;
        public String sellerName;

        // Successor
        public Shift NextShift { get; set; }

        public abstract String Work(int currentTime);
    }

    // Concrete handler.
    class SellerShift : Shift
    {
        public SellerShift(int startWrkTime, int endWrkTime, String sellerName)
        {
            _startWrkTime = startWrkTime;
            _endWrkTime = endWrkTime;
            this.sellerName = sellerName;

            if (startWrkTime > endWrkTime)
            {
                _startWrkTime = _endWrkTime = endWrkTime;
            }
        }

        public override String Work(int currentTime)
        {
            if (currentTime >= _startWrkTime && currentTime <= _endWrkTime)
            {
                return String.Format("Hello, I'm a seller {0}, what do you have in your cart?", this.sellerName);
            }
            else if (NextShift != null)
            {
                return NextShift.Work(currentTime);
            }
            return "No one works right now. This is an error"; // todo: debug?
        }

        public void SetNextShift(Shift nextShift)
        {
            if (nextShift == null)
                return;
            NextShift = nextShift;
        }
    }
}
