using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    public class Showcase
    {
        // Showcase as Singleton instance.
        static Showcase uniqueInstance;

        // Showcase Data.
        public List<WashingMachine> washingMachineStand;
        public List<Fridge> fridgeStand;
        public List<DishWasher> dishWasherStand;
        public List<TVSet> tvSetStand;

        // Public method to get instance of the showcase.
        public static Showcase Instance()
        {
            if (uniqueInstance == null)
                uniqueInstance = new Showcase();
            return uniqueInstance;
        }

        // Private constructor for singleton pattern.
        private Showcase()
        {
            this.washingMachineStand = new List<WashingMachine>();
            this.fridgeStand = new List<Fridge>();
            this.dishWasherStand = new List<DishWasher>();
            this.tvSetStand = new List<TVSet>();
            
            this.FillStandWithSamsungProducts();
            this.FillStandWithTochibaProducts();
        }

        private void FillStand(ProductManufacturer manufacturer)
        {
            washingMachineStand.Add(manufacturer.CreateWashingMachine(manufacturer.name + " Washing Machine"));
            fridgeStand.Add(manufacturer.CreateFridge(manufacturer.name + " Fridge"));
            dishWasherStand.Add(manufacturer.CreateDishWasher(manufacturer.name + " Dish Washer"));
            tvSetStand.Add(manufacturer.CreateTVSet(manufacturer.name + " TV set"));
        }

        private void FillStandWithSamsungProducts()
        {
            ProductManufacturer samsung = new SamsungProductManufacturer();
            this.FillStand(samsung);
        }

        private void FillStandWithTochibaProducts()
        {
            ProductManufacturer tochiba = new TochibaProductManufacturer();
            this.FillStand(tochiba);
        }
    }
}
