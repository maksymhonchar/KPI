#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "stack.h"

// private:
struct stack_s
{
    char data[DATA_MAXSIZE][LINE_MAXSIZE];
    int size;
};

stack_t *stack_new(void)
{
    stack_t *out = (stack_t *)malloc(sizeof(struct stack_s));
    out->size = 0;
    for(int i = 0; i < DATA_MAXSIZE; i++)
    {
        out->data[i][0] = '\0';
    }
    return (out);
}

void stack_delete(stack_t * self)
{
    free(self);
}

void stack_push(stack_t * self, char *element)
{
    if(self->size == DATA_MAXSIZE)
        return;printf("\nPrint [enter] to continue!\n");
    strcpy(self->data[self->size], element);
    self->size++;
}

char *stack_pop(stack_t * self)
{
    char *toRet;
    if(self->size == 0)
    {
        toRet = "";
        return (toRet);
    }
    toRet = self->data[self->size - 1];
    strcpy(self->data[self->size - 1], "");
    self->size--;
    return (toRet);
}

char *stack_top(stack_t * self)
{
    return (self->data[self->size - 1]);
}

void stack_print(const stack_t * self)
{
    fflush(stdin);
    printf("Size: %2i\n", stack_getSize(self));
    if(self->size == 0)
    {
        fprintf(stderr, "No items in stack.\n");
        return;
    }
    for(int i = 0; i < self->size; i++)
    {
        printf("%i: %s\n", (i + 1), self->data[i]);
    }
}

int stack_getSize(const stack_t * self)
{
    return (self->size);
}
