#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "producer.h"
#include "thread.h"
#include "mutex.h"

struct producer_s
{
    thread_t * producerThread;
};

void *_producerFunc(void *args)
{
    sharedObj_t *shObj = (sharedObj_t *)args;
    time_t t;
    srand((unsigned)time(&t));
    int index = 0;
    while(TRUE)
    {
        mutex_lock(shObj->mu);
        shObj->arr[index] = rand()%10;
        index++;
        index%=4;
        system("cls");
        printf("Array: %4i%4i%4i%4i\n", shObj->arr[0], shObj->arr[1], shObj->arr[2], shObj->arr[3]);
        printf("A process can take a while...\n\n");
        fflush(stdout);
        mutex_unlock(shObj->mu);
        Sleep(SLEEP_TIME);
    }
    return (NULL);
}

producer_t * producer_new(sharedObj_t * shObj)
{
    producer_t out;
    out.producerThread = thread_create_args(_producerFunc, shObj);
    return (&out);
}

void producer_delete(producer_t * self)
{
    thread_free(self->producerThread);
}
