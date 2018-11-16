using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;

namespace MonstersHeroesEmulator
{
    // See rules.txt for the rules, I've used so far.
    class MainTest
    {
        static void Main(string[] args)
        {
            Logger.printMsgGame("Start of the Lab 4.");

            // Creating an object.
            Console.WriteLine("Start of the test case: {0}", GC.GetTotalMemory(true));
            SwordsMan s = new SwordsMan("The man");
            for (int i = 0; i < 0xffffff; i++)
            {
                s.dump.Add((decimal)0xffffffffffffffff);
            }
            Console.WriteLine("After creating an object: {0}", GC.GetTotalMemory(true));

            // Weak reference test.
            WeakReference wr = new WeakReference(s);
            s = null;
            GC.Collect();
            s = (SwordsMan)wr.Target;
            if (s != null)
                Console.WriteLine("Swordsman is not collected!");
            else
                Console.WriteLine("Object has been collected.");

            // Dispose test.
            // Dispose is a command, that flags an object, that a program does not need it anymore.
            Console.WriteLine("Disposing an object.");
            Console.WriteLine("Before: {0}", GC.GetTotalMemory(true));
            s.Dispose();
            if (s != null)
                Console.WriteLine("Swordsman is not collected!");
            else
                Console.WriteLine("Object has been collected.");
            Console.WriteLine(GC.GetTotalMemory(true));

            // A destructor test.
            SwordsMan tmp = new SwordsMan("tmp");
            tmp = null;
            GC.Collect();

            // End of the Lab 4 test case.
            Logger.printMsgGame("End of the Lab 4.");
            Console.ReadLine();
        }
    }
}
