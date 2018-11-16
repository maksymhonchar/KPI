using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonstersHeroesEmulator
{
    internal static class PasswordManager
    {
        /// <summary>
        /// Admin access to get admin privillegy.
        /// </summary>
        private static bool isAdmin = false;

        /// <summary>
        /// Log as admin to the system.
        /// </summary>
        /// <param name="pass">Correct admin password.</param>
        public static void logAdmin(string pass)
        {
            if (String.IsNullOrEmpty(pass))
                return;

            isAdmin = (pass == "12345") ? true : false;
        }

        /// <summary>
        /// Return result if user is an admin.
        /// </summary>
        /// <returns>If user is an admin.</returns>
        public static bool isLoggedAdmin()
        {
            return isAdmin;
        }
    }
}
