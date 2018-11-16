#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "user.h"

int main()
{
    // SupaDrive entity.
    supaDrive_t *supaDrive = sd_new();
    // Users entities.
    user_t *user_maxim = user_new("Maxim");
    user_t *user_misha = user_new("Misha");
    user_t *user_katya = user_new("Katya");
    user_t *user_randomUser = user_new("RandomGuy");
    // Data in users.
    data_t *maximData = data_new("MySchool", "I hate my school");
    data_t *maximData2 = data_new("HotChicks", "Boobs yeee");
    data_t *mishaData = data_new("Calculus", "Calculus sucks");
    data_t *mishaData2 = data_new("ILoveDota", "Im a ***");
    data_t *katyaData = data_new("Girls", "Im so faat :c");
    data_t *katyaData2 = data_new("Future plans", "idc lul");
    data_t *randomGuyData = data_new("temp", "temp");
    data_setRandomData(randomGuyData);

    // Add users to supaDrive.
    sd_addUser(supaDrive, user_maxim);
    sd_addUser(supaDrive, user_misha);
    sd_addUser(supaDrive, user_katya);
    sd_addUser(supaDrive, user_randomUser);

    // Add data to users.
    user_addData(supaDrive, user_maxim, maximData, alertAddingSuccess, alertAddingWarning);
    user_addData(supaDrive, user_maxim, maximData2, alertAddingSuccess, alertAddingWarning);
    user_addData(supaDrive, user_misha, mishaData, alertAddingSuccess, alertAddingWarning);
    user_addData(supaDrive, user_misha, mishaData2, alertAddingSuccess, alertAddingWarning);
    user_addData(supaDrive, user_katya, katyaData, alertAddingSuccess, alertAddingWarning);
    user_addData(supaDrive, user_katya, katyaData2, alertAddingSuccess, alertAddingWarning);
    user_addData(supaDrive, user_randomUser, randomGuyData, alertAddingSuccess, alertAddingWarning);

    sd_printUsers(supaDrive);
    sd_printDetailedUserData(supaDrive);
    printf("\nTotal amount of data in SupaDrive: %d.\n", sd_getTotalDatasAmount(supaDrive));

    sd_deleteUser(supaDrive);
    sd_printUsers(supaDrive);
    sd_printDetailedUserData(supaDrive);
    printf("\nTotal amount of data in SupaDrive: %d.\n", sd_getTotalDatasAmount(supaDrive));

    // Free allocated memory.
    // Delete users & data.
    user_delete(user_maxim);
    user_delete(user_misha);
    user_delete(user_katya);
    user_delete(user_randomUser);
    // Delete SD entity.
    sd_delete(supaDrive);

    // End of the program.
    exit (0);
}
