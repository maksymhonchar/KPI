#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "consumer.h"
#include "thread.h"
#include "mutex.h"

struct consumer_s
{
    thread_t * consumerThread;
};

bool _checkAscending(unsigned *arr)
{
    for(int i = 0; i < SHARED_ARR_SIZE - 1; i++)
    {
        if(arr[i] >= arr[i+1])
            return (false);
    }
    return (true);
}

void *_consumerFunc(void *args)
{
    sharedObj_t *shObj = (sharedObj_t *)args;
    while(TRUE)
    {
        mutex_lock(shObj->mu);
        if(_checkAscending(shObj->arr))
        {
            puts("Array in ascending order!\n"
                 "See you later!\n"
                 "Wait +-2 seconds.");
            Sleep(2000);
        }
        mutex_unlock(shObj->mu);
        Sleep(SLEEP_TIME);
    }
    return (NULL);
}

consumer_t * consumer_new(sharedObj_t * shObj)
{
    consumer_t out;
    out.consumerThread = thread_create_args(_consumerFunc, shObj);
    return (&out);
}

void consumer_delete(consumer_t * self)
{
    thread_free(self->consumerThread);
}
