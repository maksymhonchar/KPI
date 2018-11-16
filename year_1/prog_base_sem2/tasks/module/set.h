#pragma once

#define CONSOLE_SIZE "MODE CON: COLS=70 LINES=80"

//Default fields - declared in set.c file.
typedef enum Errors_E Errors_T;
typedef struct Set_S Set_T;

//Constructor and destructor.
Set_T * Set_new(int size);
void Set_delete(Set_T * self);

//Getters and setters
int Set_getSize(const Set_T * self);
int Set_getValueAt(const Set_T * self, const int pos);
void Set_setValueAt(Set_T * self, const int pos, const int element);

//Main functions: union, intersection, difference.
Set_T * Set_union(const Set_T * first, const Set_T * second);
Set_T * Set_intersection(const Set_T * first, const Set_T * second);
Set_T * Set_difference(const Set_T * first, const Set_T * second);

//Helping functions.
int Set_removeValueAt(Set_T * self, const int pos);
void Set_fill(Set_T * self);
void Set_print(const Set_T * self);
