#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"

//private:
int _CheckIfExists(int * array, int size, int element) {
    for(int i = 0; i < size; i++) {
        if(array[i] == element)
            return (0);
    }
    return (1);
}

//public:
struct Set_S {
    int * Numbers;
    int size;
};

enum Errors_E{
    WRONG_INDEX = -1,
    NEGATIVE_NUMBER = -2,
    EMPTY_ITEM = -3
};

Set_T * Set_new(const int newSize) {
    Set_T * newSet = (Set_T *) calloc(1, sizeof(Set_T));
    newSet->Numbers = (int *) calloc(newSize, sizeof(int));
    newSet->size = newSize;
    return (newSet);
}

void Set_delete(Set_T * self) {
    free(self->Numbers);
    free(self);
}

int Set_getSize(const Set_T * self) {
    return (self->size);
}

int Set_getValueAt(const Set_T * self, const int pos) {
    if(pos >= self->size || pos < 0) {
        puts("Wrong index error.");
        return (WRONG_INDEX);
    }
    return (self->Numbers[pos]);
}

void Set_setValueAt(Set_T * self, const int pos, const int element) {
    if(pos >= self->size || pos < 0) {
        puts("Wrong index error.");
        return;
    }
    else if (element < 0) {
        puts("Wrong element error. Cannot add negative numbers.");
        return;
    }
    self->Numbers[pos] = element;
}

Set_T * Set_union(const Set_T * first, const Set_T * second) {
     int * result = (int *) calloc(first->size + second->size, sizeof(int));
     int resultIndex = 0; //shows next empty element.
     for(int i = 0; i<first->size; i++) {
        result[resultIndex] = first->Numbers[i];
        resultIndex++;
     }
     for(int i = 0; i<second->size; i++) {
        if(_CheckIfExists(first->Numbers, first->size, second->Numbers[i])) {
            result[resultIndex] = second->Numbers[i];
            resultIndex++;
        }
     }
     Set_T * unionSet = Set_new(resultIndex);
     for(int i = 0; i<unionSet->size; i++) {
        unionSet->Numbers[i] = result[i];
     }
     //Free allocated memory.
     free(result);
     return (unionSet);
}

Set_T * Set_intersection(const Set_T * first, const Set_T * second) {
    int * result = (int *) calloc(first->size + second->size, sizeof(int));
    int resultIndex = 0;
    for(int i = 0; i<first->size; i++) { //for each element from the first set
        if(!_CheckIfExists(second->Numbers, second->size, first->Numbers[i])) {
            result[resultIndex] = first->Numbers[i];
            resultIndex++;
        }
    }
    Set_T * intersectionSet = Set_new(resultIndex);
    for(int i = 0; i<intersectionSet->size; i++) {
        intersectionSet->Numbers[i] = result[i];
    }
    //Free allocated memory
    free(result);
    return (intersectionSet);
}

Set_T * Set_difference(const Set_T * first, const Set_T * second) {
    int * result = (int *) calloc(first->size + second->size, sizeof(int));
    int resultIndex = 0;
    for(int i = 0; i < first->size; i++) {
        if(_CheckIfExists(second->Numbers, second->size, first->Numbers[i])) {
            result[resultIndex] = first->Numbers[i];
            resultIndex++;
        }
    }
    Set_T * differenceSet = Set_new(resultIndex);
    for(int i = 0; i<differenceSet->size; i++) {
        differenceSet->Numbers[i] = result[i];
    }
    //Free allocated memory
    free(result);
    return (differenceSet);
}

int Set_removeValueAt(Set_T * self, const int pos) {
    if(pos >= self->size || pos < 0) {
        puts("Wrong index error.");
        return (WRONG_INDEX);
    }
    int itemToRet = self->Numbers[pos];
    for(int i = pos; i< self->size - 1; i++) {
        self->Numbers[i] = self->Numbers[i+1];
    }
    self->Numbers[self->size - 1] = EMPTY_ITEM;
    self->size--;
    return (itemToRet);
}

void Set_fill(Set_T * self) {
    for(int i = 0; i < self->size; i++)
    {
        self->Numbers[i] = i;
    }
    time_t t;
    srand((unsigned)time(&t));
    for(int i = self->size - 1; i >= 0; i--)
    {
        int j;
        if (i == 0)
            j = 1;
        else
            j = rand() % i + 1;
        int temp = self->Numbers[i];
        self->Numbers[i] = self->Numbers[j];
        self->Numbers[j] = temp;
    }
}

void Set_print(const Set_T * self) {
    if(self->size == 0) {
        printf("Set is empty.\n");
        return;
    }
    for(int i = 0; i < self->size; i++)
        printf("%d ", self->Numbers[i]);
    printf("\nCurrent size is %d\n", Set_getSize(self));
}
