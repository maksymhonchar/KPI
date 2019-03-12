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

void writer(void)
{
    do
    {
        mu_write.lock(); // Writer requests for critical section.

        // Perform the write

        mu_write.unlock(); // Leave the critical condition.
    } while (true)
}

void reader(void)
{
    do
    {
        mu_read.lock(); // Reader wants to enter the critical section.

        // The number of readers has now increased by 1.
        readcnt++;

        // There is atleast one reader in the critical section.
        // This means no writer can enter if there is even one reader.
        // Thus we give preference to readers here.
        if (readcnt == 1)
            mu_write.lock();

        // Other readers can enter while this current reader is inside the critical section.
        mu_read.unlock();

        // Perform the reading.

        // A reader wants to leave.
        mu_read.lock();

        // The number of readers has now decreased by 1.
        readcnt--;

        // That is, no reader is left in the critical section, so writers can enter.
        if (0 == readcnt) {
            mu_write.unlock();
        }
        
        mu_read.unlock(); // Reader leaves.
    } while (true);
}