using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    class Program
    {
        static void Main(string[] args)
        {
            PrototypePatternUsage();

            AbstractFabricPatternUsage();

            Console.ReadKey();
        }

        private static void PrototypePatternUsage()
        {
            FileSystem fs = FileSystem.Instance;
            Folder firstFolder = new Folder("folder1", "/lab2/folder1/");
            Folder secondFolder = new Folder("folder2", "/lab2/folder2/");
            fs.createFolder(firstFolder);
            fs.createFolder(secondFolder);
            // Load some txt files to firstFolder.
            for (int i = 0; i < 5; i++)
            {
                TextFile fileToAdd = new TextFile(String.Format("File{0}", i), firstFolder.Path);
                firstFolder.addFile(fileToAdd);
            }
            ListOfFilesFile listOfFiles = new ListOfFilesFile("MyListOfFiles", firstFolder.Path);
            firstFolder.addFile(listOfFiles);

            // Initial state of folders.
            Console.WriteLine("Initial state of folders.\n");
            Console.WriteLine(firstFolder);
            Console.WriteLine(secondFolder);
            Console.WriteLine(Environment.NewLine);

            // Task 1.1.
            // Copy list of files from folder1 to folder2.
            Console.WriteLine("Copying a list of files to the second folder.\nResult:");
            fs.copyFile(firstFolder, secondFolder, listOfFiles.getName());
            Console.WriteLine(firstFolder);
            Console.WriteLine(secondFolder);
            Console.WriteLine(Environment.NewLine);

            // Task 1.2.
            // Move list of files from folder1 to folder2.
            Console.WriteLine("Moving all files from first folder to the second folder.\nResult:");
            List<File> files = new List<File>();
            foreach (File file in firstFolder.getFilesHashtable().Values)
            {
                files.Add(file);
            }
            for (int i = 0; i < files.Count; i++)
            {
                fs.moveFile(firstFolder, secondFolder, files[i].getName());
            }
            Console.WriteLine(firstFolder);
            Console.WriteLine("");
            Console.WriteLine(secondFolder);
        }

        private static void AbstractFabricPatternUsage()
        {
            TicketClient client = new TicketClient();

            // State factory.
            Console.WriteLine("Tickets from Kyiv state.");
            TicketFactory factory = new StateFactory();
            client.printTickets(factory);
            client.printPrintedTicketsInfo();
            client.printPrintedTicketsPerks();

            Console.WriteLine(Environment.NewLine);

            // Commercial factory.
            Console.WriteLine("Tickets from SuperFactoryINC.");
            factory = new CommercialFactory();
            client.printTickets(factory);
            client.printPrintedTicketsInfo();
            client.printPrintedTicketsPerks();
        }
    }
}
