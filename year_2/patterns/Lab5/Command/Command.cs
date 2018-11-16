using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab5_Honchar_Maxim_KP_51
{
    // Command.
    abstract class Command
    {
        protected OperationUnit unit;
        protected String operand;

        public abstract void Execute();
    }

    // Concrete command.
    class Add : Command
    {
        public Add(OperationUnit unit, String operand)
        {
            this.unit = unit;
            this.operand = operand;
        }

        public override void Execute()
        {
            unit.Run('a', operand);
        }
    }

    // Concrete command.
    class Edit : Command
    {
        public Edit(OperationUnit unit, String operand)
        {
            this.unit = unit;
            this.operand = operand;
        }

        public override void Execute()
        {
            unit.Run('e', operand);
        }
    }

    // Concrete command.
    class Delete : Command
    {
        public Delete(OperationUnit unit, String operand)
        {
            this.unit = unit;
            this.operand = operand;
        }

        public override void Execute()
        {
            unit.Run('d', operand);
        }
    }

}
