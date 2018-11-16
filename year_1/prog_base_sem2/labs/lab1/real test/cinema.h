#pragma once

#include <stdbool.h> // boolean type
#include "queue.h" // queue

#define MAXPLACES 300
#define MIN_PER_HR 60.0

/* Structure to describe cinema.
    Fields:
    int places;
    queue_t * line;
*/
typedef struct cinema_s cinema_t;

// Constructor & destructor.
cinema_t * cinema_new(queue_t * line);
void cinema_delete(cinema_t * self);

// Check if client will arrive in a minute.
bool cinema_newvisitor(double x);
