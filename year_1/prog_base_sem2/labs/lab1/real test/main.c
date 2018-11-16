#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "cinema.h"

int main(void)
{
    queue_t * line = queue_new(); // Queue in the cinema
    cinema_t * cinema = cinema_new(line); // Cinema
    visitor_t * currentVisitor = visitor_new(123); // Current visitor.
    int hours; // Duration of the queue in hours.
    long perhour; // How many visitors will arrive per hour.
    double min_per_cust; // Average time between the visitors arrival.
    long cycle; // A simple counter to describe current MINUTE.
    long turnaways = 0; // How many people leaved a cinema.
    long customers = 0; // How many people connected to the queue.
    long served = 0; // How many people are IN THE CINEMA
    long sum_line = 0; // Thing for the average length of queue.
    int wait_time = 0; // Time for the service.
    long line_wait = 0; // How much time customers are already waiting in the queue.

    srand((unsigned)time(0));
    puts("- - - C I N E M A - - -");
    printf("Free places in cinema: %d\n\n", MAXPLACES);
    puts("Enter duration of the demo in hours: ");
    scanf("%d", &hours);
    puts("Enter average amount of visitors per hour: ");
    scanf("%ld", &perhour);
    min_per_cust = MIN_PER_HR / perhour;
    //1 iteration == 1 minute
    for(cycle = 0; cycle < MIN_PER_HR * hours; cycle++)
    {
        if(cinema_newvisitor(min_per_cust))
        {
            if(queue_isFull(line))
                turnaways++;
            else
            {
                visitor_delete(currentVisitor);
                currentVisitor = visitor_new(cycle);
                queue_enqueue(currentVisitor, line);
                customers++;
            }
        }
        if(wait_time <= 0 && !queue_isEmpty(line))
        {
            queue_dequeue(currentVisitor, line);
            wait_time = visitor_getProcesstime(currentVisitor);
            line_wait += cycle - visitor_getArrive(currentVisitor);
            served++;
        }
        if(wait_time > 0)
            wait_time--;
        sum_line += queue_itemCount(line);
        if(served >= MAXPLACES)
        {
            served = MAXPLACES;
            break;
        }
    }
    if(customers > 0)
    {
        printf("Into cinema: %ld\n", served);
        printf("Turnaways: %ld\n", turnaways);
        printf("Cinema is %s.\n", served == MAXPLACES ? "full" : "not full");
        printf("Average length of the queue: %.2f\n", (double)sum_line/(MIN_PER_HR * hours));
        printf("Average time of the waiting: %.2f minutes.\n", (double)line_wait/served);
    }
    else
        puts("no clients!");
    puts("- - - End of the program. - - -");
    //Free allocated memory
    cinema_delete(cinema); //delete queue HERE
    visitor_delete(currentVisitor);
    return (0);
}
