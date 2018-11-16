using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    public enum UkrainianCustomTaxes
    {
        Prepayed = 0,
        Internal = 150,
        FarEast = 250
    }

    public enum UkrainianGeneralTaxes
    {
        Prepayed = 0,
        Basic = 250,
        Complicated = 285
    }

    public interface IPriceFormerStrategy
    {
        uint GenerateProductPrice(uint basePrice);
    }

    public class SamsungProductPriceStrategy : IPriceFormerStrategy
    {
        public uint GenerateProductPrice(uint basePrice)
        {
            uint customsExpenses = (uint)UkrainianCustomTaxes.Prepayed;
            uint taxesExpenses = (uint)UkrainianGeneralTaxes.Prepayed;
            return basePrice + taxesExpenses + customsExpenses;
        }
    }

    public class TochibaProductPriceStrategy : IPriceFormerStrategy
    {
        private const double taxesCoeficient = 0.7;

        public uint GenerateProductPrice(uint basePrice)
        {
            uint customsExpenses = (uint)UkrainianCustomTaxes.FarEast;
            uint taxesExpenses = (uint)UkrainianGeneralTaxes.Complicated;
            double specialTax = (customsExpenses + taxesExpenses) * taxesCoeficient;
            return basePrice + taxesExpenses + customsExpenses + (uint)specialTax;
        }
    }

}
