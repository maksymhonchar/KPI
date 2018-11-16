using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    interface IDog
    {
        /// <summary>
        /// Basic dog action.
        /// </summary>
        /// <param name="toBark"></param>
        void Bark(string toBark = "");

        /// <summary>
        /// Dogs name.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Dogs breed.
        /// </summary>
        IBreed Breed { get; set; }
    }

    class DecoratorDog : Dog
    {
        protected Dog DecoratedDog { get; set; }
        
        public DecoratorDog(Dog decoratedDog)
        {
            this.DecoratedDog = decoratedDog;
        }

        /// <summary>
        /// Method to describe special appearance of certain breed.
        /// </summary>
        public override void DescribeAppearance()
        {
            this.DecoratedDog.DescribeAppearance();
        }
    }

    class Dog : IDog
    {
        public string Name { get; set; }

        public IBreed Breed { get; set; }

        public Dog(IBreed breed)
        {
            this.Breed = breed;
        }
        
        public void Bark(string toBark = "")
        {
            if (string.IsNullOrEmpty(toBark))
            {
                Console.WriteLine("{0} keeps being silent...", this.Name);
            }
            else
            {
                Console.WriteLine("A dog {0} tells us: {1}", this.Name, toBark);
            }
        }

        public virtual void DescribeAppearance()
        {
            Console.WriteLine("This object is a dog!");
        }
    }
}
