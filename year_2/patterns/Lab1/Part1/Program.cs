using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            /* Example for "decorator" pattern. */
            Husky husky = new Husky(new UsualDog());
            husky.DescribeAppearance();
            Bulldog bulldog = new Bulldog(new UsualDog());
            bulldog.DescribeAppearance();
            Console.ReadKey();

            Console.WriteLine(Environment.NewLine);

            /* Example for "bridge" pattern. */
            UsualDog justADog = new UsualDog();
            justADog.Bark("Hello from lab1.");
        }
    }
}
