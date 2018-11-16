using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab5_Honchar_Maxim_KP_51
{
    class InfoSystem
    {
        private OperationUnit operationUnit;
        private ControlUnit controlUnit;

        public InfoSystem()
        {
            operationUnit = new OperationUnit();
            controlUnit = new ControlUnit();
        }

        private String Run(Command command)
        {
            controlUnit.StoreCommand(command);
            controlUnit.ExecuteCommand();
            return operationUnit.Data;
        }

        public String Add(String operationValue)
        {
            return Run(new Add(operationUnit, operationValue));
        }

        public String Edit(String operationValue)
        {
            return Run(new Edit(operationUnit, operationValue));
        }

        public String Delete(String operationValue)
        {
            return Run(new Delete(operationUnit, operationValue));
        }
    }
}
