#pragma once

#define NAME_LEN 256
#define SURNAME_LEN 256
#define BIRTHDAY_LEN 256

typedef struct director_s
{
    int id;
    char name[NAME_LEN];
    char surname[SURNAME_LEN];
    int investments;
    double years;
    char birthDate[BIRTHDAY_LEN];
} director_t;

void director_print(const director_t *self);
void director_printList(const director_t *dirSet, int dirCount);
