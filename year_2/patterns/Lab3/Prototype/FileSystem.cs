using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab3_Honchar_Maxim_KP_51
{
    // This class implements a 'singleton' pattern.
    public sealed class FileSystem
    {
        private static FileSystem instance = null;
        private List<Folder> _folders = null;

        private FileSystem()
        {
            this._folders = new List<Folder>();
        }

        public static FileSystem Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new FileSystem();
                }
                return instance;
            }
        }

        public void createFolder(Folder folder)
        {
            this._folders.Add(folder);
        }

        public List<Folder> getFolders()
        {
            return this._folders;
        }

        public void moveFile(Folder folderFrom, Folder folderTo, String fileName)
        {
            File fileToMove = folderFrom.removeFile(fileName);
            folderTo.addFile(fileToMove);
        }

        public void copyFile(Folder folderFrom, Folder folderTo, String fileName)
        {
            File fileToCopy = folderFrom.getFile(fileName);
            folderTo.addFile(fileToCopy);
        }
    }

    public class Folder
    {
        public String Name { get; private set; }
        public String Path { get; private set; }

        private Hashtable _files;

        public Folder(String name, String path)
        {
            this.Name = name;
            this.Path = path;
            this._files = new Hashtable();
        }

        public void addFile(File file)
        {
            _files[file.getName()] = file;
        }

        public File getFile(String filename)
        {
            File fileToGet = this.getFileInstance(filename);
            return (File)fileToGet.Clone();
        }

        public File removeFile(String filename)
        {
            File fileToRemove = this.getFileInstance(filename);
            if (fileToRemove != null)
            {
                _files.Remove(filename);
            }
            return fileToRemove;
        }

        private File getFileInstance(String filename)
        {
            return (File)_files[filename];
        }

        public Hashtable getFilesHashtable()
        {
            return _files;
        }

        public override string ToString()
        {
            string toReturn = "Folder " + this.Name + "\n";
            if (_files.Count == 0)
            {
                toReturn += "This folder is empty.";
            }
            else
            {
                toReturn += "Files:\n";
                foreach (DictionaryEntry entry in _files)
                {
                    File fileToLookAt = (File)entry.Value;
                    toReturn += fileToLookAt.getPath() + "\n";
                }
            }
            return toReturn;
        }

    }
}
