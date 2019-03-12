/*
src: http://www.modernescpp.com/index.php/reader-writer-locks

NOTE: the program uses std::shared_timed_mutex and std::shared_lock - since c++14

std::lock_guard - mutex wrapper that provides mechanism for owning a mutex for the duration of a scoped block.
*/

#include <iostream>
#include <vector>
#include <shared_mutex>
#include <thread>

// Critical region - threads will compete for access to it.
std::vector<int> grades{5, 5, 4, 5, 3, 4};

// Main mutex.
std::shared_timed_mutex grades_vect_mu;

// Writer.
void add_grade(const int new_grade)
{
    std::lock_guard<std::shared_timed_mutex> writer_lock(grades_vect_mu);

    std::cout << "Writing information to 'grades'.\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Sleep for adequate printing.

    grades.push_back(new_grade);

    std::cout << "Writing OK.\n";
}

// Reader.
void print_grades(int thread_id)
{
    std::shared_lock<std::shared_timed_mutex> reader_lock(grades_vect_mu);

    std::cout << "Hello from thread " << thread_id << ". Grades are ";
    for (int i = 0; i < grades.size(); i++)
    {
        std::cout << grades[i] << " | ";
    }
    std::cout << ".\n";
}

// Test.
int main(int argc, char const *argv[])
{
    std::thread reader_threads[8];
    for (int i = 0; i < 8; i++)
    {
        reader_threads[i] = std::thread(print_grades, i);
    }
    std::thread writer1(add_grade, 1);
    std::thread writer2(add_grade, 2);

    for (int i = 0; i < 8; i++)
    {
        reader_threads[i].join();
    }
    writer1.join();
    writer2.join();

    std::cout << "Updated vector is: ";
    for (int i = 0; i < grades.size(); i++)
    {
        std::cout << grades[i] << " | ";
    }
    std::cout << ".\n";

    return EXIT_SUCCESS;
}
