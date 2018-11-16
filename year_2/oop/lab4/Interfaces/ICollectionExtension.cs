using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonstersHeroesEmulator
{
    public interface ICollectionExtension
    {
        void Clear();
    }

    public static class CollectionExtension
    {
        public static void Clear(this ICollectionExtension extension, string reason)
        {
            Console.WriteLine("The collection should be cleared!");
            Console.WriteLine("Reason: {0}", reason);
            extension.Clear();
        }
    }
}
