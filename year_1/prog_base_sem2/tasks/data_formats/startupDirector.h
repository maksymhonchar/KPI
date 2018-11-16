#pragma once

#include <time.h> // time_t

#define DIRECTOR_NAME_LEN 50
#define DIRECTOR_SURNAME_LEN 50
#define DIRECTOR_NATIONALITY_LEN 50
#define STARTUP_NAME_LEN 100

#define DIRECTORS_COUNT 4

typedef struct Startup_S
{
    char name[STARTUP_NAME_LEN];
    int budget;
} Startup_T;

typedef struct Director_S
{
    char name[DIRECTOR_NAME_LEN];
    char surname[DIRECTOR_SURNAME_LEN];
    char nationality[DIRECTOR_NATIONALITY_LEN];
    struct tm birthDate;
    int enthusiasm;
    float experience;
    int money;
    struct Startup_S startup;
} Director_T;

Director_T *director_new(void);
void director_delete(Director_T *director);
Startup_T *startup_new(void);
void startup_delete(Startup_T *startup);

void xmlParse(Director_T *directorSet[], const char * XMLFileName);
void printDirectorInfo(Director_T *director);
