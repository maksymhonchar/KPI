#pragma once

#include "sharedObject.h"

// Structure do describe producer thread.
typedef struct producer_s producer_t;

// Constructor.
producer_t * producer_new(sharedObj_t * shObj);

// Destructor.
void producer_delete(producer_t * self);
