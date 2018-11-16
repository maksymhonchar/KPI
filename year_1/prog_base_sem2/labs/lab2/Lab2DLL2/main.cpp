#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "main.h"

void addItem(stack_t * a)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int randomLength = rand() % 6 + 3;
    char randomStr[randomLength];
    // Generate random string
    for(int i = 0; i < randomLength - 1; i++)
        randomStr[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    randomStr[randomLength] = '\0';
    // Push string to stack!
    printf("\nPushing %s to stack...", randomStr);
    stack_push(a, randomStr);
    _getch();
    system("cls");
    stack_print(a);
}

void reaction(stack_t * a)
{
    if(stack_getSize(a) != DATA_MAXSIZE)
    {
        printf("No reaction.\n");
        Sleep(500);
        return;
    }
    int itemsToDelete = strlen(stack_top(a));
    printf("\nStack if full!\nDelete %i items...\n", itemsToDelete);
    Sleep(2000);
    printf("3...\n");
    Sleep(1000);
    printf("2...\n");
    Sleep(1000);
    printf("1...\n");
    Sleep(1000);
    for(int i = 0; i < itemsToDelete; i++)
    {
        if(!stack_getSize(a))
            break;
        stack_pop(a);
    }
    printf("Press [enter]");
    _getch();
    system("cls");
    stack_print(a);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // succesful
}
