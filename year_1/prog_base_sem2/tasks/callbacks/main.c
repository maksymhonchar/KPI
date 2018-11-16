#include <stdio.h> // gets puts printf
#include <strings.h> // strlen

#include "callbacks.h"

int main()
{
    char str[USERINPUT_MAX];
    // Get user input
    printf("Your string: ");
    gets(str);
    puts("");
    // Call check function with check1 alert1 CBfunctions set.
    puts("check1 & alert1");
    check(str, strlen(str), check1, alert1);
    puts("");
    // Call check function with check2 alert2 CBfunctions set.
    puts("check2 & alert2");
    check(str, strlen(str), check2, alert2);
    puts("");
    // End of the program.
    puts("end of the program.");
    return 0;
}

