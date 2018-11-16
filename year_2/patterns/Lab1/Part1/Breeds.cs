using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    interface IBreed
    {
        /// <summary>
        /// Each breed has its own special talent action.
        /// </summary>
        void BreedTalent();
    }

    class UsualDog : Dog
    {
        public UsualDog(IBreed breed)
            : base(breed)
        {
            this.Name = "A usual dog";
        }
    }

    /// <summary>
    /// A hunting breed.
    /// </summary>
    class Husky : DecoratorDog, IBreed
    {
        private int rabbitCatched;

        public Husky(Dog decoratedDog)
            : base(decoratedDog)
        {
            this.rabbitCatched = 0;
        }

        public void BreedTalent()
        {
            Console.WriteLine("Husky catched a rabbit! Now it has {0} of them.", this.rabbitCatched);
        }

        public override void DescribeAppearance()
        {
            base.DescribeAppearance();
            Console.WriteLine("Husky has a special tail.");
        }
    }

    /// <summary>
    /// A fighting breed.
    /// </summary>
    class Bulldog : DecoratorDog, IBreed
    {
        private int enemiesWon;

        public Bulldog(Dog decoratedDog)
            : base(decoratedDog)
        {
            this.enemiesWon = 0;
        }

        public void BreedTalent()
        {
            bool won = false;
            Random r = new Random();
            if (r.Next(10) > 5)
            { 
                enemiesWon++;
                won = true;
            }
            Console.WriteLine("A bulldog starts a fight. ");
            Console.Write("He {0} and has {1} wins.", won ? "won" : "lost", enemiesWon);
        }

        public override void DescribeAppearance()
        {
            base.DescribeAppearance();
            Console.WriteLine("Bulldog has a cute muzzle.");
        }
    }
}
