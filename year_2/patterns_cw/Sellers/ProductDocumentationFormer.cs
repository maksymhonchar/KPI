using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Course_Work_Honchar_Maxim_KP_51
{
    // "Facade" design pattern.
    class ProductDocumentationFormer
    {
        MainProductDocumentation mainDoc;
        WarrantyCard warrantyCard;
        SaleContract saleContract;

        public ProductDocumentationFormer()
        {
            this.mainDoc = new MainProductDocumentation();
            this.warrantyCard = new WarrantyCard();
            this.saleContract = new SaleContract();
        }

        public List<String> FormDocumentationPackage(Product product)
        {
            Console.WriteLine("Docs for {0} are formed.", product.name);
            return new List<string>() { mainDoc.ToString(), warrantyCard.ToString(), saleContract.ToString() };
        }
    }

    // Abstract class for facade subclasses.
    abstract class ProductDocument
    {
        public string Name;

        public override string ToString()
        {
            return String.Format("{0} document", Name);
        }
    }

    // Example of facade subclass.
    class MainProductDocumentation : ProductDocument
    {
        public MainProductDocumentation()
        {
            this.Name = "Main product documentation.";
        }
    }

    class WarrantyCard : ProductDocument
    {
        public WarrantyCard()
        {
            this.Name = "Warranty card";
        }
    }

    class SaleContract : ProductDocument
    {
        public SaleContract()
        {
            this.Name = "Sale contract";
        }
    }
}
