using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class TochibaWashingMachine : WashingMachine
    {
        public TochibaWashingMachine(uint price, ProductColor color, String name, int rpmNum)
        {
            this.name = name;
            this.category = "Washing machine";
            this.color = color;
            this.price = price;
            this.rpmNumber = rpmNum;
            this.manufacturer = "Tochiba";
        }
    }

    class TochibaFridge : Fridge
    {
        public TochibaFridge(uint price, ProductColor color, String name, bool hasFreezer)
        {
            this.name = name;
            this.category = "Fridge";
            this.color = color;
            this.price = price;
            this.hasFreezer = hasFreezer;
            this.manufacturer = "Tochiba";
        }
    }

    class TochibaDishWasher : DishWasher
    {
        public TochibaDishWasher(uint price, ProductColor color, String name, int capacityInKg)
        {
            this.name = name;
            this.category = "Dish washer";
            this.color = color;
            this.price = price;
            this.capacityInKg = capacityInKg;
            this.manufacturer = "Tochiba";
        }
    }

    class TochibaTVSet : TVSet
    {
        public TochibaTVSet(uint price, ProductColor color, String name, double diagonal)
        {
            this.name = name;
            this.category = "TV set";
            this.color = color;
            this.price = price;
            this.screenDiagonal = diagonal;
            this.manufacturer = "Tochiba";
        }
    }
}
