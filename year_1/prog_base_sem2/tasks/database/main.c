#include <stdio.h>
#include <stdlib.h>

#include "director.h"
#include "dbModule.h"

#define DIRECTORS_MAX_COUNT 100
#define DATABASE_PATH "Director.db"

#define FILTER_MAXINVESTMENTS 350000
#define FILTER_MINYEARS 1.5

int main()
{
    db_t * db = database_new(DATABASE_PATH);
    director_t directorList_filter[DIRECTORS_MAX_COUNT];

    // Count overall directors amount.
    int directorsCount = database_countDirectors(db);
    printf("Directors total in database: [%d]", directorsCount);
    printf("\n\n");

    // Count how much directors have certain 'investments' and 'years' fields.
    int filterCount = database_filterDirectors(db, FILTER_MAXINVESTMENTS, FILTER_MINYEARS, directorList_filter, directorsCount);
    printf("Directors with \n1)less than [%d] investments;\n2)more than [%.3f] years of existance;\n>%d",
           FILTER_MAXINVESTMENTS, FILTER_MINYEARS, filterCount);
    printf("\n\n");

    // Print these directors.
    printf("List of directors with certain statement:\n\n");
    director_printList(directorList_filter, filterCount);
    printf("\n\n");

    // Get director with id=5
    printf("Director with id 5:\n");
    director_t *directorToCheckId = database_getDirectorById(db, 5);
    director_print(directorToCheckId);
    printf("\n\n");

    // Update director with id=1 (it was Maxim-Gonchar-1mln-1.0-19980708
    printf("Updating director with id 1 (See comments in main).\n");
    director_t directorForUpdateFunc = {20, "UpdatedMaxim", "UpdatedGonchar", 2000000, 2.0, "1998-07-08"};
    database_updateDirector(db, &directorForUpdateFunc, 1);
    printf("\n\n");

    // Uncomment to paste data into database.
    /*
    // Add a new director to the database.
    printf("Adding new director to database...\n");
    director_t directorToPaste = {0, "AmazingName", "AmazingSurname", 1000, 5.0, "1990-09-09"};
    database_insertDirector(db, &directorToPaste);
    */

    // Uncomment to delete data from database.
    /*
    // Delete director from the database.
    printf("Deleting director from database...\n");
    database_deleteDirectorById(db, 5);
    */

    return 0;
}
