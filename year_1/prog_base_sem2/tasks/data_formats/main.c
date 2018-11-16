#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <libxml/tree.h>

#include "startupDirector.h"

/* Define to check that the libxml version in use
is compatible with the version the software has
been compiled against */
#ifndef LIBXML_TEST_VERSION
#define LIBXML_TEST_VERSION
#endif

int main()
{
    const char *filePath = "StartupDirector.xml";
    Director_T *directors[DIRECTORS_COUNT];

    // Init directors array
    for(int i = 0; i < DIRECTORS_COUNT; i++)
    {
        directors[i] = director_new();
    }

    // Parse elements from .xml file.
    xmlParse(directors, filePath);

    // Print parsed info.
    for(int i = 0; i < DIRECTORS_COUNT; i++)
    {
        printf("STARTUP_DIRECTOR #%i\n", (i+1));
        printDirectorInfo(directors[i]);
    }

    // Free allocated memory
    for(int i = 0; i < DIRECTORS_COUNT; i++)
    {
        director_delete(directors[i]);
    }
    return 0;
}
