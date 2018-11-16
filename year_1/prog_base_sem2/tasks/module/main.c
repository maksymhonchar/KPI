#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int main() {
    //Set console default size.
    system(CONSOLE_SIZE);
    //Testing fields
    int testSize = 10;
    Set_T * mainSet = Set_new(testSize);

    //Fill the set
    Set_fill(mainSet);
    //Print it out
    puts("**********");
    printf("Creating a new set...\n"
           "Filling it with non-repeatable numbers...\n");
    Set_print(mainSet);
    puts("**********");
    //Get some elements
    printf("Getting element on the index 4...\n");
    int test_a = Set_getValueAt(mainSet,4);
    printf("Element with the index 4 is %d\n", test_a);
    printf("Getting element on the index 10...\n");
    int test_b = Set_getValueAt(mainSet,10);
    printf("Element with the index 10 is %d\n", test_b);
    //Set some elements
    printf("Setting element with index 3 to \"123\"\n");
    Set_setValueAt(mainSet, 3, 123);
    printf("Setting element with index 10 to \"123\"\n");
    Set_setValueAt(mainSet, 10, 123);
    //Print set again
    puts("**********");
    Set_print(mainSet);
    //Delete some elements
    printf("Deleting element index 3\n");
    Set_removeValueAt(mainSet, 3);

    //Print the set again
    puts("**********");
    Set_print(mainSet);
    //In the end - free allocated memory
    puts("----------------------------------------------------------------------");
    printf("Creating two more sets.\n");
    Set_T * first = Set_new(testSize+1);
    Set_T * second = Set_new(testSize+4); //15
    Set_fill(first);
    Set_fill(second);
    puts("**********");
    printf("First set:\n");
    Set_print(first);
    printf("Second set:\n");
    Set_print(second);
    puts("**********");
    printf("Union with the first set and the second set.\n");
    Set_T * test_unionSet = Set_union(first, second);
    printf("The 'union' set:\n");
    Set_print(test_unionSet);
    puts("**********");
    printf("Intersection with the first and the second set.\n");
    Set_T * test_intersectionSet = Set_intersection(first, second);
    printf("The 'intersection' set:\n");
    Set_print(test_intersectionSet);
    puts("**********");
    printf("Difference between the first and the second set.\n");
    for(int i = 0; i < Set_getSize(first); i++) {
        Set_setValueAt(first, i, 8+i);
    }
    printf("Changed first set:\n");
    Set_print(first);
    Set_T * test_differenceSet = Set_difference(first, second);
    printf("The 'difference' set:\n");
    Set_print(test_differenceSet);
    puts("**********");
    //free allocated memory
    Set_delete(first);
    Set_delete(second);
    Set_delete(mainSet);
    Set_delete(test_unionSet);
    Set_delete(test_intersectionSet);
    Set_delete(test_differenceSet);
    puts("allocated memory was deleted.");
    return (0);
}
