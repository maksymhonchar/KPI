#pragma once

#include "sharedObject.h"

// Structure do describe consumer thread.
typedef struct consumer_s consumer_t;

// Constructor.
consumer_t * consumer_new(sharedObj_t * shObj);

// Destructor.
void consumer_delete(consumer_t * self);
