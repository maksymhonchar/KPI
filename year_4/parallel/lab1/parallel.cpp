#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <unistd.h>

static const long MATRIX_SIZE = 6000;
static const int THREADS_NUMBER = 8;

std::mutex mx;

// Shared resources.
float max_elem = 0;
int max_elem_i_index;
int max_elem_j_index;

struct Matrix
{
    float **elements;

    void initialize_zero()
    {
        elements = new float *[MATRIX_SIZE];
        for (int i = 0; i < MATRIX_SIZE; ++i)
        {
            elements[i] = new float[MATRIX_SIZE];
            for (int j = 0; j < MATRIX_SIZE; ++j)
            {
                elements[i][j] = 0.0f;
            }
        }
    }
    void initialize_random()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-1000.0, 1000.0);
        elements = new float *[MATRIX_SIZE];
        for (int i = 0; i < MATRIX_SIZE; ++i)
        {
            elements[i] = new float[MATRIX_SIZE];
            for (int j = 0; j < MATRIX_SIZE; ++j)
            {
                elements[i][j] = dist(mt);
            }
        }
    }

    void print()
    {
        std::cout << std::endl;
        for (int i = 0; i < MATRIX_SIZE; ++i)
        {
            std::cout << "|\t";

            for (int j = 0; j < MATRIX_SIZE; ++j)
            {
                std::cout << elements[i][j] << "\t";
            }
            std::cout << "|" << std::endl;
        }
    }
};

void multithreading_execution(Matrix &r, const Matrix &m1, const Matrix &m2);
void multiply_threading(Matrix &result, const int thread_number, const Matrix &m1, const Matrix &m2);
void search_max(Matrix &m, const int thread_number);
void search_max_elem_execution(Matrix &m);

int main()
{
    // 4000 elems 8 threads  -> 158sec
    // 4000 elems 20 threads -> 229sec ?!
    // 6000 elems 8 threads -> 8min; 25861microseconds; Biggest element is 1.41448e+08on [2366,4876].

    Matrix result_matrix;
    Matrix m1, m2;

    result_matrix.initialize_zero();
    m1.initialize_random();
    m2.initialize_random();

    multithreading_execution(result_matrix, m1, m2);

    usleep(3000000);

    search_max_elem_execution(result_matrix);
}

void multiply_threading(Matrix &result, const int thread_number, const Matrix &m1, const Matrix &m2)
{
    // Calculate workload
    const int n_elements = (MATRIX_SIZE * MATRIX_SIZE);      // # of elements of the matrix == size of the 1-dimensional array.
    const int n_operations = n_elements / THREADS_NUMBER;    // # of operations that each specific thread has to do.
    const int rest_operations = n_elements % THREADS_NUMBER; // # of operations that are left and someone has to do == does the first thread..

    int start_op, end_op;

    if (thread_number == 0)
    {
        // First thread does more job - it does "rest_operations".
        start_op = n_operations * thread_number;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }
    else
    {
        start_op = n_operations * thread_number + rest_operations;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }

    for (int op = start_op; op < end_op; ++op)
    {
        // Sleep(100000);
        std::cout << "thread " << thread_number << ". op=" << op << "\n";
        const int row = op % MATRIX_SIZE;
        const int col = op / MATRIX_SIZE;
        float r = 0.0f;
        for (int i = 0; i < MATRIX_SIZE; ++i)
        {
            const float e1 = m1.elements[row][i];
            const float e2 = m2.elements[i][col];
            r += e1 * e2;
        }

        result.elements[row][col] = r;
    }
}

void multithreading_execution(Matrix &r, const Matrix &m1, const Matrix &m2)
{

    std::chrono::high_resolution_clock::time_point before_multiplication = std::chrono::high_resolution_clock::now();

    std::thread threads[THREADS_NUMBER];

    for (int i = 0; i < THREADS_NUMBER; ++i)
    {
        threads[i] = std::thread(multiply_threading, std::ref(r), i, std::ref(m1), std::ref(m2));
    }

    for (int i = 0; i < THREADS_NUMBER; ++i)
    {
        threads[i].join();
    }

    std::chrono::high_resolution_clock::time_point after_multiplication = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(after_multiplication - before_multiplication).count();
    std::cout << "Multiplication duration, seconds: " << duration << "\n";
}

void search_max(Matrix &m, const int thread_number)
{
    // Calculate workload
    const int n_rows = MATRIX_SIZE / THREADS_NUMBER;      // # of rows for each thread to work on.
    const int n_remainder = MATRIX_SIZE % THREADS_NUMBER; // # of additional rows for thread1.

    int start_row, end_row;

    if (thread_number == 0)
    {
        // First thread does more job - it does "rest_operations".
        start_row = n_rows * thread_number + n_remainder;
        end_row = (n_rows * (thread_number + 1)) + n_remainder;
    }
    else
    {
        start_row = n_rows * thread_number + n_remainder;
        end_row = (n_rows * (thread_number + 1)) + n_remainder;
    }

    for (int cur_row = start_row; cur_row < end_row; ++cur_row)
    {
        for (int i = 0; i < MATRIX_SIZE; ++i)
        {
            mx.lock();
            if (m.elements[cur_row][i] > max_elem)
            {
                max_elem = m.elements[cur_row][i];
                max_elem_i_index = cur_row;
                max_elem_j_index = i;
                std::cout << "thread " << thread_number << ". Found biggest element " << max_elem << "on [" << max_elem_i_index << "," << max_elem_j_index << "].\n";
            }
            mx.unlock();
        }
    }
}

void search_max_elem_execution(Matrix &m)
{
    std::chrono::high_resolution_clock::time_point before_maxsearch = std::chrono::high_resolution_clock::now();

    std::thread threads[THREADS_NUMBER];

    for (int i = 0; i < THREADS_NUMBER; ++i)
    {
        threads[i] = std::thread(search_max, std::ref(m), i);
    }

    for (int i = 0; i < THREADS_NUMBER; ++i)
    {
        threads[i].join();
    }

    std::chrono::high_resolution_clock::time_point after_maxsearch = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(after_maxsearch - before_maxsearch).count();
    std::cout << "Search duration, microseconds: " << duration << "\n";
    std::cout << "Biggest element is " << max_elem << "on [" << max_elem_i_index << "," << max_elem_j_index << "].\n";
}
