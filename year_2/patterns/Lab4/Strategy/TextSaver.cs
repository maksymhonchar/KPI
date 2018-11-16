using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab4_Honchar_Maxim_KP_51
{
    public class TextSaver
    {
        private ITextSavingStrategy _textSaver;
        private String _filePath;

        public TextSaver(String filePath)
        {
            _filePath = filePath;
        }

        public void SetTextSaver(ITextSavingStrategy textSaver)
        {
            if (textSaver == null)
                return;
            _textSaver = textSaver;
        }

        public void SetFilePath(String filePath)
        {
            _filePath = filePath;
        }

        public void SaveText(String textToSave)
        {
            _textSaver.SaveTextToFile(textToSave, _filePath);
        }
    }

    public interface ITextSavingStrategy
    {
        String SaveTextToFile(string textToSave, string filePath);
    }

    public class CasualTextSaver : ITextSavingStrategy
    {
        public String SaveTextToFile(string textToSave, string filePath)
        {
            Console.WriteLine("No need to process input text.");
            Console.WriteLine("Text \"{0}\" was saved to {1} with casual text saver.", textToSave, filePath);
            return textToSave;
        }
    }

    public class DeleteSpacesTextSaver : ITextSavingStrategy
    {
        public String SaveTextToFile(string textToSave, string filePath)
        {
            String textWithoutSpaces = textToSave.Replace(" ", String.Empty);
            Console.WriteLine("Input text \"{0}\" was processed to {1}", textToSave, textWithoutSpaces);
            Console.WriteLine("Text \"{0}\" was saved to {1} with \"NoSpaces(c)\" text saver.", textWithoutSpaces, filePath);
            return textWithoutSpaces;
        }
    }

    public class EncodeTextSaver : ITextSavingStrategy
    {
        public String SaveTextToFile(string textToSave, string filePath)
        {
            String encodedText = textToSave.Replace(" ", "|||");
            Console.WriteLine("Input text \"{0}\" was processed to {1}", textToSave, encodedText);
            Console.WriteLine("Text \"{0}\" was saved to {1} with encoder text saver.", encodedText, filePath);
            return encodedText;
        }
    }

}
