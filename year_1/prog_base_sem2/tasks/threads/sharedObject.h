#pragma once

#include "mutex.h"
#define SHARED_ARR_SIZE 4
#ifndef TRUE
   #define TRUE 1
#endif
#define SLEEP_TIME 30

typedef struct sharedObj_s
{
    unsigned arr[SHARED_ARR_SIZE];
    mutex_t *mu;
} sharedObj_t;
