/*
Considering a shared Database our objectives are:
- Readers can access database only when there are no writers.
- Writers can access database only when there are no readers or writers.
- Only one thread can manipulate the state variables at a time.

Basic structure of a solution:
Writer()
   Wait until no active readers or writers
   Access database
   Check out – wake up waiting readers or writer
Reader()
   Wait until no writers
   Access database
   Check out – wake up a waiting writer

Fairness rule:
- Once a reader is waiting, readers will get in next AND writers queue up.
- If a writer is waiting, one writer will get in next AND readers queue up.
*/

#include <mutex>

// Readers/Writers state variables.
int readers_cnt = 0;
int waiting_readers_cnt = 0;
int writers_cnt = 0;
int waiting_writers_cnt = 0;

// Readers/Writers mutexes.
std::mutex can_read;
std::mutex can_write;

void start_write()
{
    // A writer can enter if there are no other active writers and no readers are waiting.
    if (writers_cnt == 1 || readers_cnt > 0)
    {
        waiting_writers_cnt++;

        can_write.lock();

        waiting_writers_cnt--;
    }

    writers_cnt = 1;
}

void end_write()
{
    writers_cnt = 0;

    // Checks to see if any readers are waiting - fairness rule.
    if (waiting_readers_cnt)
    {
        can_read.unlock();
    }
    else
    {
        can_write.unlock();
    }
}

void start_read()
{
    // A reader can enter if there are no writers active or waiting,
    // so we can have many readers active all at once.
    if (writers_cnt == 1 || waiting_writers_cnt > 0)
    {
        waiting_readers_cnt++;

        can_read.lock();

        waiting_readers_cnt--;
    }

    readers_cnt++;

    can_read.unlock();
}

void end_read()
{
    readers_cnt--;

    // When a reader finishes, if it was the last reader, it lets a writer in (if any is there).
    if (0 == readers_cnt)
        can_write.unlock();
}
