using System;

namespace MonstersHeroesEmulator
{
    class MainTest
    {
        static void Main(string[] args)
        {
            // Testing interfaces, abstract classes, delegate-event-handler.
            SwordsMan hero_sm = new SwordsMan("Maxim");
            Boss monst_boss = new Boss("MegaBoss");
            Console.WriteLine(hero_sm);
            Console.WriteLine(monst_boss);

            // Testing raising an exception.
            for (int i = 0; i < 10; i++)
            {
                try
                {
                    monst_boss.dealDamage(hero: hero_sm);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Message: {0}", ex.Message);
                    Console.WriteLine("Target method: {0}", ex.TargetSite);
                    Console.WriteLine("InnerException: {0}", ex.InnerException);
                }
            }            

            // End of the Lab 2 test case.
            Logger.printMsgGame("\nEnd of the Lab 2.");
            Console.ReadLine();
        }
    }
}
