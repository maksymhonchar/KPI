using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;


namespace MonstersHeroesEmulator
{
    class MainTest
    {
        static void Main(string[] args)
        {
            Logger.printMsgGame("Start of the Lab 3.");

            // Testing usage of anonymous methods, lambdas and Func/Actions.
            // Test1_AnonMethods();
            // Test2_Lambdas();
            // Test3_FuncAction();
            // Test4_CustomCollection();

            // Test 5: a custom enum.
            /*
             SwordsMan s = new SwordsMan("The man");
            s.AddSkill(GameUtils.Skills.Aftershock);
            s.AddSkill(GameUtils.Skills.Invasion);
             */

            // Serialization.
            // Test6_BinarySerialization();
            // Test7_XMLSerialization();

            // End of the Lab 3 test case.
            Logger.printMsgGame("End of the Lab 3.");
            Console.ReadLine();
        }

        static void Test1_AnonMethods()
        {
            SwordsMan s = new SwordsMan("Maxim");
            Boss b = new Boss("MegaBoss");
            s.HeroHit += delegate () { Console.WriteLine("psst, someone will attack this hero soon!"); };
            b.MonsterHit += delegate () { Console.WriteLine("psst, someone will attack this monster soon!"); };

            Console.WriteLine("");
            b.dealDamage(hero: s);
            Console.WriteLine("");
            s.dealDamage(monster: b);
            Console.WriteLine(Environment.NewLine);
        }

        static void Test2_Lambdas()
        {
            SwordsMan s = new SwordsMan("Maxim");
            Boss b = new Boss("MegaBoss");
            s.HeroHit += () => { Console.WriteLine("psst, someone will attack this hero soon!"); };
            b.MonsterHit += () => { Console.WriteLine("psst, someone will attack this monster soon!"); };

            Console.WriteLine("");
            b.dealDamage(hero: s);
            Console.WriteLine("");
            s.dealDamage(monster: b);
            Console.WriteLine(Environment.NewLine);
        }

        static void Test3_FuncAction()
        {
            SwordsMan s = new SwordsMan("Maxim");

            // Print position before and after moving a hero on the map.
            Console.WriteLine(s.getSpecificPosition());
            s.moveHero(20, 20);
            Console.WriteLine(s.getSpecificPosition());

            Console.WriteLine("");

            // Print position before and after moving a hero on the map.
            Console.WriteLine(s.getSpecificPosition());
            s.moveHero(200, 200);
            Console.WriteLine(s.getSpecificPosition());
        }

        static void Test4_CustomCollection()
        {
            // Testing a custom collection of objects.

            // Test4.1: test an indexer.
            JacketForAwards j1 = new JacketForAwards();
            j1.Add(new Tuple<string, int>("the best ever", 5));
            Console.WriteLine(j1["0x05"]);

            Tuple<string, int> tmp = new Tuple<string, int>("the second tuple", 15);
            j1.Add(tmp);
            Console.WriteLine(j1["0x0F"]);

            // Test 4.2: sorting.
            JacketForAwards j2 = new JacketForAwards();
            j2.Add(new Tuple<string, int>("the third tuple", 100));
            j2.Add(new Tuple<string, int>("the fifth tuple", 50));
            j2.Add(new Tuple<string, int>("the fifth tuple", 75 ));
            j2.Add(new Tuple<string, int>("the sixth tuple", -25));
            j2.Add(new Tuple<string, int>("the seventh tuple", 12));
            j2.Add(new Tuple<string, int>("the fourth tuple", -25));
            JacketForAwards j3 = new JacketForAwards();
            j3.Add(new Tuple<string, int>("the fifth tuple", 0));
            j3.Add(new Tuple<string, int>("the sixth tuple", -25));
            j3.Add(new Tuple<string, int>("the seventh tuple", 12));
            List<JacketForAwards> jList = new List<JacketForAwards>();
            jList.Add(j1);
            jList.Add(j2);
            jList.Add(j3);
            jList.Sort();
            foreach (var jacket in jList)
                Console.WriteLine(jacket);

            // Test 4.3.: cycling through collection.
            foreach (var tpl_awards in j2)
            {
                Console.WriteLine(tpl_awards);
            }

            // Test 4.4.: collection extension.
            // Clearing JacketForAwards j2.
            j2.Clear("This method is extended.");
        }

        static void Test6_BinarySerialization()
        {
            SwordsMan h = new SwordsMan("Maxim");
            Console.WriteLine(h);

            // Serialize to Binary.
            Console.WriteLine("Start serialization");
            FileStream fs = new FileStream("swordsman.dat", FileMode.Create);
            BinaryFormatter bf = new BinaryFormatter();
            bf.Serialize(fs, h);
            fs.Close();

            // Deserialize from Binary.
            Console.WriteLine("Start deserialization");
            FileStream fs2 = new FileStream("swordsman.dat", FileMode.Open);
            BinaryFormatter bf2 = new BinaryFormatter();
            SwordsMan h2 = (SwordsMan)bf2.Deserialize(fs2);
            fs2.Close();

            // Print the result.
            Console.WriteLine("Before");
            Console.WriteLine(h);
            Console.WriteLine("After");
            Console.WriteLine(h2);
        }

        static void Test7_XMLSerialization()
        {
            Sword h = new Sword("TheBestSword", 100, 100);
            Sword h2 = new Sword("TheWorstSword", 5, 10);
            Sword[] swords = new Sword[] { h, h2 };
            Sword[] h_des;

            // Serialize object.
            SoapFormatter formatter = new SoapFormatter();
            using (FileStream fs = new FileStream("swordsman.soap", FileMode.OpenOrCreate))
            {
                formatter.Serialize(fs, swords);
                Console.WriteLine("Serialization completed.");
            }

            // Deserialize object.
            using (FileStream fs = new FileStream("swordsman.soap", FileMode.OpenOrCreate))
            {
                h_des = (Sword [])formatter.Deserialize(fs);
                Console.WriteLine("Deserialization completed.");
            }

            Console.WriteLine("Objects after serialization:");
            foreach (var sword in swords)
            {
                Console.WriteLine(sword);
            }
        }
    }
}
