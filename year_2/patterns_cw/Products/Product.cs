using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    public enum ProductColor
    {
        Red = 1,
        Green,
        Blue,
        Black,
        White
    }

    public abstract class Product
    {
        public String name;
        public String category;
        public String manufacturer;
        public ProductColor color;
        public uint price;

        public override string ToString()
        {
            return String.Format("{0}; {1}UAH", name, price);
        }
    }

    public abstract class WashingMachine : Product
    {
        public int rpmNumber;
    }

    public abstract class Fridge : Product
    {
        public bool hasFreezer;
    }

    public abstract class DishWasher : Product
    {
        public int capacityInKg;
    }

    public abstract class TVSet : Product
    {
        public double screenDiagonal;
    }
}
