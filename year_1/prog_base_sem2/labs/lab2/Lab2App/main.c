#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "stack.h"

typedef int (*add_f)(stack_t * a);
typedef void (*react_f)(stack_t * a);

typedef struct dynamic_s
{
    HANDLE hLib;
    add_f add;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);
const char * userChoice();

int main()
{
    stack_t * testStack = stack_new();

    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll)
    {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->add)
    {
        printf("Can't get adding function!\n");
        return 1;
    }
    if (NULL == dll->react)
    {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    Sleep(1000);
    system("cls");
    stack_print(testStack);
    while(1)
    {
        fflush(stdin);
        dll->add(testStack);
        dll->react(testStack);
        Sleep(100);
    }
    stack_delete(testStack);
    dynamic_clean(dll);
    return 0;
}

const char * userChoice()
{
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2)
    {
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1)
        {
            return "C:\\Users\\maxgo\\Desktop\\Lab2DLL1\\bin\\Release\\Lab2DLL1.dll";
            //return "Lab2DLL1.dll";
        }
        else if (dllNum == 2)
        {
            return "C:\\Users\\maxgo\\Desktop\\Lab2DLL2\\bin\\Release\\Lab2DLL2.dll";
            //return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName)
{
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->add = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib)
    {
        dyn->add = (add_f)GetProcAddress(dyn->hLib, "addItem");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    }
    else
    {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn)
{
    FreeLibrary(dyn->hLib);
    free(dyn);
}
