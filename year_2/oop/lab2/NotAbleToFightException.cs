using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonstersHeroesEmulator
{
    public class NotAbleToFightException : Exception
    {
        const string errorMsg = "Fatal error: a game model is not able to fight.";

        public NotAbleToFightException()
        {
            this.LogErrorMessage();
        }

        public NotAbleToFightException(string message)
            : base(message)
        {
            this.LogErrorMessage();
            this.Source = "SwordsMan.NotAbleToFightException";
        }

        public NotAbleToFightException(string message, Exception inner)
            : base(String.Format("{0} - {1}", errorMsg, message), inner)
        {
            this.LogErrorMessage();
        }

        private void LogErrorMessage()
        {
            Logger.LogMessage(errorMsg);
        }
    }
}
