#include <stdio.h>
#include <conio.h>

#include "mutex.h"
#include "producer.h"
#include "consumer.h"

int main()
{
    // Shared data structure.
    sharedObj_t sharedObject = { {0,0,0,0} };
    sharedObject.mu = mutex_new();

    // Create and run primary threads/
    producer_t * producer1 = producer_new(&sharedObject);
    consumer_t * consumer1 = consumer_new(&sharedObject);
    producer_t * producer2 = producer_new(&sharedObject);
    consumer_t * consumer2 = consumer_new(&sharedObject);

    // Wait here.
    _getch();

    // Delete threads and free allocated memory.
    producer_delete(producer1);
    consumer_delete(consumer1);
    producer_delete(producer2);
    consumer_delete(consumer2);
    // Delete mutex.
    mutex_free(sharedObject.mu);

    // End of the program
    puts("End of the program.");
    return (0);
}
