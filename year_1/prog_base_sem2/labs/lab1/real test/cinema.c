#include <stdlib.h>
#include "cinema.h"

// private encapsulated structure:
struct cinema_s {
    int places;
    queue_t * line;
};

// public functions:
cinema_t * cinema_new(queue_t * line)
{
    cinema_t * out = (cinema_t *) malloc(sizeof(cinema_t));
    out->places = MAXPLACES;
    out->line = line;
    return (out);
}
void cinema_delete(cinema_t * self)
{
    queue_delete(self->line);
    free(self);
}
bool cinema_newvisitor(double x)
{
    if(rand() * x / RAND_MAX < 1)
        return (true);
    else
        return (false);
}
