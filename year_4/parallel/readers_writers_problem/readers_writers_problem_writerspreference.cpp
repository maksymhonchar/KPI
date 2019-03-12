/*
src: https://www.geeksforgeeks.org/readers-writers-problem-set-1-introduction-and-readers-preference-solution/

Readers-Writers problem, preference solution.

Consider a situation where we have a file shared between many people.
- If one of the people tries editing the file, no other person should be reading or writing at the same time, otherwise changes will not be visible to him/her.
- However if some person is reading the file, then others may read it at the same time.

Problem parameters:
- One set of data is shared among a number of processes
- Once a writer is ready, it performs its write. Only one writer may write at a time
- If a process is writing, no other process can read it
- If at least one reader is reading, no other process can write
- Readers may not write and only read
*/

#include <mutex>

std::mutex mu_read;
std::mutex mu_write;

int readcnt = 0;
int writecnt = 0;

void writer(void)
{
    do
    {
        mu_write.lock(); // Writer requests for critical section.

        writecnt++;

        if (1 == writecnt)
            mu_read.lock();

        mu_write.unlock();

        // Perform the write

        mu_write.lock();

        if (0 == writecnt)
            mu_read.unlock();

        writecnt--;

        mu_write.unlock(); // Leave the critical condition.
    } while (true)
}

void reader(void)
{
    do
    {
        mu_read.lock(); // Reader wants to enter the critical section.

        // Perform the reading.

        mu_read.unlock(); // Reader leaves.
    } while (true);
}