/*
Source: Wikipedia

In computing, the producer–consumer problem is a classic example of a multi-process synchronization problem.

The problem describes two processes, the producer and the consumer, who share a common, fixed-size buffer used as a queue. The producer's job is to generate data, put it into the buffer, and start again. At the same time, the consumer is consuming the data (i.e., removing it from the buffer), one piece at a time. 

The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer won't try to remove data from an empty buffer.

The solution for the producer is to either go to sleep or discard data if the buffer is full. The next time the consumer removes an item from the buffer, it notifies the producer, who starts to fill the buffer again. In the same way, the consumer can go to sleep if it finds the buffer empty. The next time the producer puts data into the buffer, it wakes up the sleeping consumer.

The solution can be reached by means of inter-process communication, typically using semaphores. 
An inadequate solution could result in a deadlock where both processes are waiting to be awakened. The problem can also be generalized to have multiple producers and consumers.
*/

/*
std::lock_guard - mutex wrapper that provides mechanism for owning a mutex for the duration of a scoped block.
When a lock_guard object is created, it attempts to take ownership of the mutex it is given. When control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and the mutex is released.

std::condition_variable - a synchronization primitive that can be used to block a thread, or multiple threads at the same time, until another thread both modifies a shared variable (the condition), and notifies the condition_variable.
*/

/*
g++ producer_consumer.cpp -lpthread
g++ -pthread producer_consumer.cpp
*/

#include <thread>
#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>

std::mutex mx;
std::condition_variable cv;
std::queue<int> q;

bool finished = false;

void producer(int n)
{
    for (int i = 0; i < n; i++)
    {
        {
            std::lock_guard<std::mutex> lk(mx);
            q.push(i);
            std::cout << "pushing " << i << std::endl;
        }
        cv.notify_all();
    }
    {
        std::lock_guard<std::mutex> lk(mx);
        finished = true;
    }
    cv.notify_all();
}

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mx);
        cv.wait(lk, [] { return finished || !q.empty(); });
        while (!q.empty())
        {
            std::cout << "consuming " << q.front() << std::endl;
            q.pop();
        }
        if (finished)
            break;
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(producer, 100);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    std::cout << "finished!" << std::endl;

    return 0;
}
