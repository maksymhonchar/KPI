#include <stdlib.h> // cmocka unit-tests
#include <stddef.h> // cmocka unit-tests
#include <stdarg.h> // cmocka unit-tests
#include <setjmp.h> // cmocka unit-tests

#include <cmocka.h>

#include "queue.h"
#include "cinema.h"

#define TEST_LONG 1000

// Unit-test for queue_new, visitor_new, cinema_new methods.
static void queueNew_visitorNew_cinemaNew__oneLong__memoryAllocated(void ** state)
{
    queue_t *testQueue = queue_new();
    visitor_t *testVisitor = visitor_new(TEST_LONG);
    cinema_t *testCinema = cinema_new(testQueue);
    assert_non_null(testQueue);
    assert_non_null(testVisitor);
    assert_non_null(testCinema);
}

// Unit-test for visitor_getProcesstime, visitor_getArrive methods.
static void visitor_getProcesstime_getArrive__oneVisitor__fieldsNonZero(void ** state)
{
    visitor_t *testVisitor = visitor_new(TEST_LONG);
    assert_int_equal((int)TEST_LONG, (int)visitor_getArrive(testVisitor));
    assert_in_range(visitor_getProcesstime(testVisitor), 1, 3);
}

// Unit-test for queue_isFull queue_isEmpty methods.
static void queue_isFull_isEmpty__oneVisitor__currentState(void ** state)
{
    #ifdef MAXQUEUE
        #undef MAXQUEUE
    #endif // MAXQUEUE
    #ifndef MAXQUEUE
        #define MAXQUEUE 100
    #endif // MAXQUEUE
    queue_t *testQueue = queue_new();
    assert_true(queue_isEmpty(testQueue));
    assert_false(queue_isFull(testQueue));
}

// Unit-test for queue_enqueue, queue_dequeue and queue_itemCount methods.
static void queue_itemCount_enqueue_dequeue__oneVisitor__addingDeletingCorrect(void ** state)
{
    visitor_t *testVisitor = visitor_new(TEST_LONG);
    queue_t *testQueue = queue_new();
    queue_enqueue(testVisitor, testQueue);
    queue_enqueue(testVisitor, testQueue);
    assert_int_equal(queue_itemCount(testQueue), 2);
    queue_dequeue(testVisitor, testQueue);
    assert_int_equal(queue_itemCount(testQueue), 1);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(queueNew_visitorNew_cinemaNew__oneLong__memoryAllocated),
        cmocka_unit_test(visitor_getProcesstime_getArrive__oneVisitor__fieldsNonZero),
        cmocka_unit_test(queue_isFull_isEmpty__oneVisitor__currentState),
        cmocka_unit_test(queue_itemCount_enqueue_dequeue__oneVisitor__addingDeletingCorrect),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
