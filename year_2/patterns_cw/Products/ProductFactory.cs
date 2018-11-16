using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    // Abstract factory pattern.
    abstract class ProductManufacturer
    {
        public List<ProductColor> factoryProductsColors;
        public String name;

        protected ProductPriceFormer priceFormer = new ProductPriceFormer();
        protected Random rand = new Random();

        public abstract WashingMachine CreateWashingMachine(String name);
        public abstract Fridge CreateFridge(String name);
        public abstract DishWasher CreateDishWasher(String name);
        public abstract TVSet CreateTVSet(String name);
    }

    class SamsungProductManufacturer : ProductManufacturer
    {
        public SamsungProductManufacturer()
        {
            this.factoryProductsColors = new List<ProductColor>()
            {
                ProductColor.Green,
                ProductColor.Red,
                ProductColor.Blue
            };
            this.name = "Samsung";
            this.priceFormer.SetProductPriceStrategy(new SamsungProductPriceStrategy());
        }

        public override WashingMachine CreateWashingMachine(String name)
        {
            return new SamsungWashingMachine(
                this.priceFormer.GetProductPrice((uint)rand.Next(1000, 2000)),
                this.factoryProductsColors[rand.Next(3)],
                name,
                rand.Next(200, 500)
            );
        }

        public override Fridge CreateFridge(String name)
        {
            return new SamsungFridge(
                this.priceFormer.GetProductPrice((uint)rand.Next(2000, 3000)),
                this.factoryProductsColors[rand.Next(3)],
                name,
                true
            );
        }

        public override DishWasher CreateDishWasher(String name)
        {
            return new SamsungDishWasher(
                this.priceFormer.GetProductPrice((uint)rand.Next(1500, 2500)),
                this.factoryProductsColors[rand.Next(3)],
                name,
                rand.Next(10, 80)
            );
        }

        public override TVSet CreateTVSet(String name)
        {
            return new SamsungTVSet(
                this.priceFormer.GetProductPrice((uint)rand.Next(10000, 20000)),
                this.factoryProductsColors[rand.Next(3)],
                name,
                rand.NextDouble() * 10
            );
        }
    }

    class TochibaProductManufacturer : ProductManufacturer
    {
        public TochibaProductManufacturer()
        {
            this.factoryProductsColors = new List<ProductColor>()
            {
                ProductColor.Black,
                ProductColor.White
            };
            this.name = "Tochiba";
            this.priceFormer.SetProductPriceStrategy(new TochibaProductPriceStrategy());
        }

        public override WashingMachine CreateWashingMachine(String name)
        {
            return new TochibaWashingMachine(
                this.priceFormer.GetProductPrice((uint)rand.Next(1800, 2800)),
                this.factoryProductsColors[rand.Next(2)],
                name,
                rand.Next(200, 500)
            );
        }

        public override Fridge CreateFridge(String name)
        {
            return new TochibaFridge(
                this.priceFormer.GetProductPrice((uint)rand.Next(1200, 1750)),
                this.factoryProductsColors[rand.Next(2)],
                name,
                false
            );
        }

        public override DishWasher CreateDishWasher(String name)
        {
            return new TochibaDishWasher(
                this.priceFormer.GetProductPrice((uint)rand.Next(600, 1500)),
                this.factoryProductsColors[rand.Next(2)],
                name,
                rand.Next(10, 80)
            );
        }

        public override TVSet CreateTVSet(String name)
        {
            return new TochibaTVSet(
                this.priceFormer.GetProductPrice((uint)rand.Next(9000, 14000)),
                this.factoryProductsColors[rand.Next(2)],
                name,
                rand.NextDouble() * 10
            );
        }
    }
}
