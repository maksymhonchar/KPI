using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class SamsungWashingMachine : WashingMachine
    {
        public SamsungWashingMachine(uint price, ProductColor color, String name, int rpmNum)
        {
            this.name = name;
            this.category = "Washing machine";
            this.color = color;
            this.price = price;
            this.rpmNumber = rpmNum;
            this.manufacturer = "Samsung";
        }

    }

    class SamsungFridge : Fridge
    {
        public SamsungFridge(uint price, ProductColor color, String name, bool hasFreezer)
        {
            this.name = name;
            this.category = "Fridge";
            this.color = color;
            this.price = price;
            this.hasFreezer = hasFreezer;
            this.manufacturer = "Samsung";
        }
    }

    class SamsungDishWasher : DishWasher
    {
        public SamsungDishWasher(uint price, ProductColor color, String name, int capacityInKg)
        {
            this.name = name;
            this.category = "Dish washer";
            this.color = color;
            this.price = price;
            this.capacityInKg = capacityInKg;
            this.manufacturer = "Samsung";
        }
    }

    class SamsungTVSet : TVSet
    {
        public SamsungTVSet(uint price, ProductColor color, String name, double diagonal)
        {
            this.name = name;
            this.category = "TV set";
            this.color = color;
            this.price = price;
            this.screenDiagonal = diagonal;
            this.manufacturer = "Samsung";
        }
    }
}
