using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab5_Honchar_Maxim_KP_51
{
    class OperationUnit
    {
        public String Data { get; private set; }

        public void Run(char operationCode, String operationValue)
        {
            switch (operationCode)
            {
                case 'a':
                    Data += operationValue;
                    break;
                case 'd':
                    Data = String.Empty;
                    break;
                case 'e':
                    Data = operationValue;
                    break;
                default:
                    break;
            }
        }

    }
}
