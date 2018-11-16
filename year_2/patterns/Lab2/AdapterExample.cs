using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Lab2_Honchar_Maxim_KP_51
{
    class OldishCompany
    {
        protected string _name;
        protected string _surname;
        protected string _mailAddress;
        protected string _login;
        protected string _password;
        protected string _secretWord;

        public virtual void SignUp()
        {
            Console.WriteLine("Oldish company SignUp");
            _name = specialReadLine("Your name");
            _surname = specialReadLine("Your surname");
            _mailAddress = specialReadLine("Your mail address");
            _login = specialReadLine("Your login");
            _password = specialReadLine("Your password");
            _secretWord = specialReadLine("Your secret word");
        }
        
        public void Display()
        {
            Console.WriteLine("User info:" +
                "{0}-{1}; {2}; {3}-{4}", _name, _surname, _mailAddress, _login, _password);
        }

        protected string specialReadLine(string caption)
        {
            Console.Write("{0}: ", caption);
            return Console.ReadLine();
        }
    }

    // The 'Adapter' class.
    class NewishCompany : OldishCompany
    {
        // The adaptee in adapter - a new feature.
        private RegisterSystem _regSys;

        public override void SignUp()
        {
            Console.WriteLine("Newish company SignUp");
            _login = specialReadLine("(+) Your login");
            _password = specialReadLine("(+) Your password");
            _secretWord = specialReadLine("(+) Your secret word");

            // Implementing new features from 'Adaptee'.
            _regSys = new RegisterSystem();
            _name = _regSys.GetName();
            _surname = _regSys.GetSurname();
            _mailAddress = _regSys.GetMailAddress();
        }
    }

    // The 'Adaptee' class.
    class RegisterSystem
    {
        public string GetName()
        {
            Console.Write("{0}: ", "(-) Your name");
            return specialStringPrompt("SysDefaultName");
        }

        public string GetSurname()
        {
            Console.Write("{0}: ", "(-) Your surname");
            return specialStringPrompt("SysDefaultSurname");
        }

        public string GetMailAddress()
        {
            Console.Write("{0}: ", "(-) Your mail");
            return specialStringPrompt("SysDefaultMail");
        }

        private string specialStringPrompt(string defaultValue)
        {
            string tmp = Console.ReadLine();
            return (tmp != string.Empty ? tmp : defaultValue);
        }
    }
}
