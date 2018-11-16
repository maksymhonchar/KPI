#include <stdio.h>

#include "main.h"

void addItem(stack_t * a)
{
    char userInput[100];
    printf("\nEnter string to add:\n");
    fgets(userInput, 100, stdin);
    stack_push(a, userInput);
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
    printf("Stack if full!\nHow much elements should program delete?\n>");
    int usrInput = 0;
    scanf("%i", &usrInput);
    for(int i = 0; i < usrInput; i++) {
      if(!stack_getSize(a))
         break;
      stack_pop(a);
    }
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
