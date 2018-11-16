using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    class GameMain
    {
        static void placeModelsOnMap(Model model, double posX = 10, double posY = 10)
        {
            model.setSpecificPosition(posX, posY);
        }

        static void Main(string[] args)
        {
            // Create instances for heroes and monsters.
            Logger.printMsgGame("Game is creating instances for heroes and monsters.");
            SwordsMan hero_sm = new SwordsMan("Maxim");
            WeakKnight hero_wk = new WeakKnight();
            Boss monst_boss = new Boss("MegaBoss");
            CasualMonster monst_cm = new CasualMonster();

            Model[] models = new Model[] {
                hero_sm, hero_wk,
                monst_boss, monst_cm
            };

            // Create two additional Model instances for testing only.
            Logger.printMsgGame("Game is creating instances of Model for testing.");
            Model testingModel_1 = new Model();
            Model testingModel_2 = new Model(80, 4.5, 4.5);
            testingModel_1.setSpecificPosition(10, 10);

            // Place monsters on the map.
            Logger.printMsgGame("Game is placing monsters on the map.");
            foreach (Model model in models)
                model.setSpecificPosition(10, 10);

            // Introduce heroes and monsters.
            Logger.printMsgGame("Game is introducing heroes and monsters.");
            Logger.printMsgGame("At the moment there are following models in the game:");
            foreach (Model model in models)
                Logger.simplePrint("->" + model.ToString());

            // Make a fight between heroes and monsters.
            Logger.printMsgGame("Game is creating a fight.");
            Logger.printMsgGame("Swordsman starts hitting boss.");
            hero_sm.dealDamage(monster: monst_boss);
            Logger.printMsgGame("Weak knight starts hitting a boss.");
            hero_wk.dealDamage(monster: monst_boss);
            Logger.printMsgGame("Boss starts hitting a weakknight.");
            monst_boss.dealDamage(hero: hero_wk);
            Logger.printMsgGame("Casual monster starts hitting a weakknight.");
            monst_cm.dealDamage(hero: hero_wk);

            // Try to do critical hits.
            Logger.printMsgGame("Heroes and monsters start doing critical hits.");
            Logger.printMsgGame("Swordsman does a critical hit to boss!");
            hero_sm.doCritical(monster: monst_boss);
            Logger.printMsgGame("Weak knight does a critical hit to boss!");
            hero_wk.doCritical(monster: monst_boss);
            Logger.printMsgGame("Boss does a critical hit to weakknight!");
            monst_boss.doCritical(hero: hero_sm);
            Logger.printMsgGame("Casual monster does a critical hit to weakknight!");
            monst_cm.doCritical(hero: hero_sm);

            // Print result of the battle.
            Logger.printMsgGame("HP after the battle:");
            Logger.simplePrint("->" + hero_sm.getCurrentHealth());
            Logger.simplePrint("->" + hero_wk.getCurrentHealth());
            Logger.simplePrint("->" + monst_boss.getCurrentHealth());
            Logger.simplePrint("->" + monst_cm.getCurrentHealth());

            Console.WriteLine();
            Logger.printMsgGame("End of the program");
        }
    }
}
