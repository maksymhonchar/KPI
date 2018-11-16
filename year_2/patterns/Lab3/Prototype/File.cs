using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    // Abstract prototype.
    public abstract class File : ICloneable
    {
        protected const char _folderDelimeter = '/';

        protected String name;
        protected String path;
        protected String extension;

        public Object Clone()
        {
            Object clone = null;
            try
            {
                clone = this.MemberwiseClone();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            return clone;
        }

        public String getPath()
        {
            path = this.correctLastCharacterInPath(path);
            return String.Format("{0}{1}.{2}", this.path, this.name, this.extension);
        }

        public String getName()
        {
            return this.name;
        }

        private String correctLastCharacterInPath(String path)
        {
            char lastPathCharacter = path[path.Length - 1];
            if (lastPathCharacter != _folderDelimeter)
            {
                path += _folderDelimeter;
            }
            return path;
        }

        public override string ToString()
        {
            return this.getPath();
        }
    }

    // Concrete prototype 1.
    class TextFile : File
    {
        public String Content { get; set; }

        public TextFile(String name, String path)
        {
            this.name = name;
            this.path = path;
            this.extension = "txt";
        }
    }

    // Concrete prototype 2.
    class ListOfFilesFile : File
    {
        public List<String> content;

        public ListOfFilesFile(String name, String path)
        {
            this.name = name;
            this.path = path;
            this.extension = "lst";
            this.content = new List<string>();
        }

        public void addFileNameToContent(File file)
        {
            this.content.Add(file.ToString());
        }

        public void addFileNameListToContent(List<File> listOfFiles)
        {
            foreach (File file in listOfFiles)
            {
                this.content.Add(file.ToString());
            }
        }
    }
}
