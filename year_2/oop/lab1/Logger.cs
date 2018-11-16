using System;
using System.Linq;
using System.IO;
using System.Collections.Generic;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class to help user build an appropriate log file.</para>
    /// <para>printMsg(string contents) - write message into console.</para>
    /// <para>writeMsg(string contents) - write message only into the log.</para>
    /// </summary>
    internal static class Logger
    {
        internal static string loggerVersion = "v0.0.1";
        private static string logFilePath;
        private static string userName;
        private static string promptSystem;
        private static string promptPlayer;
        private static string promptGame;

        static Logger()
        {
            Console.ForegroundColor = ConsoleColor.White;
            logFilePath = formLogFilePath("log.txt");
            userName = System.Security.Principal.WindowsIdentity.GetCurrent().Name;
            promptSystem = userName + "@system:~ $ ";
            promptPlayer = userName + "@player:~ $ ";
            promptGame = userName + "@game:~ $ ";
            printGreetings();
        }

        /// <summary>
        /// <para>Form an appropriate path for the log file, that can be used for writing a log.</para>
        /// </summary>
        /// <param name="logFileName">Actual log filename.</param>
        /// <returns>Full log path.</returns>
        private static string formLogFilePath(string logFileName)
        {
            // Get a folder to save a log file.
            string[] dirsNames = Directory.GetCurrentDirectory().Split('\\');
            IEnumerable<string> dirsList = dirsNames.Take(dirsNames.Length - 2);
            string logFilePath = "";
            foreach (var item in dirsList)
            {
                logFilePath += item + @"\";
            }

            // Check if file with name "d.m.yyyy.log" already exists.
            // If it does - save it into *_v{N}.log, where {N} is a number. 
            int dummyCounter = 0;
            string possibleName = string.Format(@"{0:d/M/yyyy}.log", DateTime.Now);
            while (File.Exists(logFilePath + possibleName))
            {
                possibleName = String.Format(@"\{0:d/M/yyyy}_v{1}.log", DateTime.Now, ++dummyCounter);
            }

            // Return a file path with appropriate filename.
            return logFilePath + possibleName;
        }

        /// <summary>
        /// <para>Print a greetings to the user. Display info about logger creation, user, log filepath.</para>
        /// </summary>
        private static void printGreetings()
        {
            Console.WriteLine("{0}Logger {1} has been created.", promptSystem, loggerVersion);
            Console.WriteLine("{0}You are using a program under {1} account.", promptSystem, userName);
            Console.WriteLine("{0}A log file will be saved to following path: {1}.\n", promptSystem, logFilePath);
        }

        /// <summary>
        /// <para>Print a message to the console and write it into the .log file as an admin.</para>
        /// </summary>
        /// <param name="contents">Message to be printed and written to the log.</param>
        public static void printMsgSystem(string contents)
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write(promptSystem);
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(contents);
            writeMsg(contents, role: "System");
        }

        /// <summary>
        /// <para>Print a message to the console and write it into the .log file as an user.</para>
        /// </summary>
        /// <param name="contents">Message to be printed and written to the log.</param>
        public static void printMsgPlayer(string contents)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write(promptPlayer);
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(contents);
            writeMsg(contents, role: "Player");
        }

        /// <summary>
        /// <para>Print a message to the console and write it into the .log file as a game object.</para>
        /// </summary>
        /// <param name="contents">Message to be printed and written to the log.</param>
        public static void printMsgGame(string contents)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("\n" + promptGame);
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(contents);
            writeMsg(contents, role: "Game");
        }

        public static void simplePrint(string contents)
        {
            Console.WriteLine(contents);
            writeMsg(contents, "");
        }

        /// <summary>
        /// <para>Write a message into the .log file.</para>
        /// </summary>
        /// <param name="contents">Message to be written.</param>
        private static void writeMsg(string contents, string role)
        {
            string toWrite = "";
            if (role == "")
            {
                toWrite = String.Format("{0} {1}", contents, Environment.NewLine);
            }
            else
            {
                toWrite = String.Format("[{0}] - {1}{2}", role, contents, Environment.NewLine);
            }
            File.AppendAllText(logFilePath, toWrite);
        }
    }
}
