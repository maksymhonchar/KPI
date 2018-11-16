#include <stdio.h> // printf puts

#include "callbacks.h"

//private:
void alert1(void) { puts("from alert1: I knew it!"); }
void alert2(void) { puts("from alert2: Really?"); }
void alert3(void) { puts("from alert3: No changes."); }

//public:
void check1(const char l, const char r, alertCB alertSample)
{
    if(l > r)
    {
        printf("Calling alertFunction for [%c] and [%c]!\n", l, r);
        alertSample();
        return;
    }
    printf("[%c] is less/equal than [%c]\n", l, r);
    alertSample = &alert3;
    alertSample();
}

void check2(const char l, const char r, alertCB alertSample)
{
    if(r > l)
    {
        printf("Calling alertFunction for [%c] and [%c]!\n", l, r);
        alertSample();
        return;
    }
    printf("[%c] is less/equal than [%c]\n", r, l);
    alertSample = &alert3;
    alertSample();
}

void check(const char *str, const size_t size, checkCB checkSample, alertCB alertSample)
{
    for(size_t i = 0; i < size - 1; i++) //size-1 to avoid \0 character.
    {
        checkSample(str[i], str[i+1], alertSample);
    }
}
