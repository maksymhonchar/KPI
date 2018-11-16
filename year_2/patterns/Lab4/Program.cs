using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab4_Honchar_Maxim_KP_51
{
    class Program
    {
        static void Main(string[] args)
        {
            StatePatternExample();

            Console.WriteLine(Environment.NewLine);

            StrategyPatternExample();

            Console.ReadKey();
        }

        private static void StatePatternExample()
        {
            DiscountCardContext card = new DiscountCardContext();

            Console.WriteLine("Paying 5000 UAH.");
            card.Pay(5000);

            Console.WriteLine("");

            Console.WriteLine("Paying 5000 UAH.");
            card.Pay(5000);

            Console.WriteLine("");

            Console.WriteLine("Paying 5000 UAH.");
            card.Pay(5000);

            Console.WriteLine("");

            Console.WriteLine("Paying 5000 UAH.");
            card.Pay(5000);

            Console.WriteLine(Environment.NewLine);

            Console.WriteLine("Print info about card:");
            Console.WriteLine(card.ToString());

            Console.WriteLine();
        }

        private static void StrategyPatternExample()
        {
            const String textExample = "Text example for lab 3";

            TextSaver ts = new TextSaver("/lab3/filePath1");
            CasualTextSaver casualTS = new CasualTextSaver();
            DeleteSpacesTextSaver nospacesTS = new DeleteSpacesTextSaver();
            EncodeTextSaver encoderTS = new EncodeTextSaver();

            ts.SetTextSaver(casualTS);
            ts.SaveText(textExample);

            Console.WriteLine(Environment.NewLine);

            ts.SetTextSaver(nospacesTS);
            ts.SaveText(textExample);

            Console.WriteLine(Environment.NewLine);

            ts.SetTextSaver(encoderTS);
            ts.SaveText(textExample);
        }
    }
}
