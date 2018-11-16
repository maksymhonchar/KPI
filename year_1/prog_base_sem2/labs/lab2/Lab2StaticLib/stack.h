#pragma once

#define DATA_MAXSIZE 10
#define LINE_MAXSIZE 100

typedef struct stack_s stack_t;

// Constructor.
stack_t *stack_new(void);

// Destructor.
void stack_delete(stack_t * self);

// Default methods.
void stack_push(stack_t * self, char * element);
char *stack_pop(stack_t * self);
char *stack_top(stack_t * self);

// Additional methods.
void stack_print(const stack_t * self);
int stack_getSize(const stack_t * self);
