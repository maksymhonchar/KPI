#include <stdio.h>

#include "director.h"

void director_print(const director_t *self)
{
    printf("Name: %s\n"
           "Surname: %s\n"
           "Investments: %i\n"
           "Years: %.2f\n"
           "Birthdate: %s\n",
           self->name,
           self->surname,
           self->investments,
           self->years,
           self->birthDate);
}

void director_printList(const director_t *dirSet, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%i.", (i+1));
        director_print(&dirSet[i]);
        printf("");
    }
}
