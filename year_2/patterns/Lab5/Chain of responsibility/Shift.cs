using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab5_Honchar_Maxim_KP_51
{
    // Abstract handler.
    public abstract class Shift
    {
        protected int _startWrkTime;
        protected int _endWrkTime;
        
        // Successor
        public Shift NextShift { get; set; }

        public abstract void Work(int currentTime);

        public abstract void SetWorkingMsg(String msg);
    }

    // Concrete handler.
    public class FactoryShift : Shift
    {
        private String _workingMsg;
        private bool dummyFlag = false;

        public FactoryShift(int startWrkTime, int endWrkTime)
        {
            _startWrkTime = startWrkTime;
            _endWrkTime = endWrkTime;
            _workingMsg = "Shift starts working";

            if (startWrkTime > endWrkTime)
            {
                _startWrkTime -= 24;
            }
        }

        public override void Work(int currentTime)
        {
            if (currentTime > _startWrkTime && currentTime <= (_endWrkTime - 1))
            {
                Console.WriteLine(_workingMsg);
            }
            else if (NextShift != null)
            {
                NextShift.Work(currentTime);
            }
        }

        public void SetNextShift(Shift nextShift)
        {
            if (nextShift == null)
                return;
            NextShift = nextShift;
        }

        public override void SetWorkingMsg(String msg)
        {
            if (msg == null)
                return;
            _workingMsg = msg;
        }
    }
}
