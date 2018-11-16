using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    class ProductPriceFormer
    {
        private IPriceFormerStrategy _manufacturerPriceStrategy;

        public void SetProductPriceStrategy(IPriceFormerStrategy manufacturerStrategy)
        {
            if (manufacturerStrategy == null)
                return;
            _manufacturerPriceStrategy = manufacturerStrategy;
        }

        public uint GetProductPrice(uint productBasePrice)
        {
            return _manufacturerPriceStrategy.GenerateProductPrice(productBasePrice);
        }
    }
}
