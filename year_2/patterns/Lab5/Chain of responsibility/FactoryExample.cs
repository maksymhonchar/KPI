using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab5_Honchar_Maxim_KP_51
{
    class FactoryExample
    {
        private Shift _firstShift;
        private Shift _secondShift;
        private Shift _thirdShift;
        
        public FactoryExample()
        {
            _firstShift = new FactoryShift(6, 15);
            _firstShift.SetWorkingMsg("First shift starts working.");
            _secondShift = new FactoryShift(14, 23);
            _secondShift.SetWorkingMsg("Second shift starts working.");
            _thirdShift = new FactoryShift(22, 7);
            _thirdShift.SetWorkingMsg("Third shift starts working.");
            this.SetSchedule();
        }

        public void SetWork(int time)
        {
            if (time < 0 || time > 24)
            {
                return;
            }

            // try to give a job to any shift.
            _firstShift.Work(time);
        }

        private void SetSchedule()
        {
            _firstShift.NextShift = _secondShift;
            _secondShift.NextShift = _thirdShift;
            _thirdShift.NextShift = _firstShift;
        }
    }
}
