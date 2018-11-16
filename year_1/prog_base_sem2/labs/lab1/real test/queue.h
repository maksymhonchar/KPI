#pragma once

#include <stdbool.h> //boolean type

#define MAXQUEUE 100

/* Structure to describe visitor.
    Fields:
    long arrive;
    int processtime;
*/
typedef struct visitor_s visitor_t;

/* Node type.
    Fields:
    visitor_t visitor;
    struct node_s * next;
*/
typedef struct node_s node_t;

/* Queue ADT.
    Fields:
    node_t *front
    node_t *rear
    int items
*/
typedef struct queue_s queue_t;

// Constructors.
queue_t * queue_new();
visitor_t * visitor_new(long when);

// Destructor's.
void queue_delete(queue_t * self);
void visitor_delete(visitor_t * self);

// Getters for visitor
long visitor_getArrive(const visitor_t * self);
int visitor_getProcesstime(const visitor_t * self);

// Queue essential functions.
bool queue_isFull(const queue_t * self);
bool queue_isEmpty(const queue_t * self);
int queue_itemCount(const queue_t * self);

// Adding & deleting an item to the queue.
bool queue_enqueue(visitor_t * visitor, queue_t * self);
bool queue_dequeue(visitor_t * visitor_deleted, queue_t * self);
