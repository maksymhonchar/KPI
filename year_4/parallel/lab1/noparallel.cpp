#include <iostream>
#include <random>
#include <chrono>

int **result;
int **m1;
int **m2;

void multiply_sq_matrices(int **m1, int **m2, int **res, size_t msize)
{
    int i, j, k;
    for (size_t i = 0; i < msize; i++)
    {
        std::cout << i << "\n";
        for (size_t j = 0; j < msize; j++)
        {
            res[i][j] = 0;
            for (size_t k = 0; k < msize; k++)
            {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    // 4000 elements -> 599 sec.

    if (argc < 2)
    {
        std::cout << "Please pass amount of square matrice columns.";
        return EXIT_FAILURE;
    }

    std::random_device rd;  //Will be used to obtain a seed for the random number engine.
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd().
    std::uniform_int_distribution<> dis(1, 100);

    int matrices_size = std::atoi(argv[1]);
    result = new int *[matrices_size];
    m1 = new int *[matrices_size];
    m2 = new int *[matrices_size];

    for (size_t i = 0; i < matrices_size; i++)
    {
        std::cout << i << "\n";
        result[i] = new int[matrices_size];
        m1[i] = new int[matrices_size];
        m2[i] = new int[matrices_size];
        for (size_t j = 0; j < matrices_size; j++)
        {
            m1[i][j] = dis(gen);
            m2[i][j] = dis(gen);
        }
    }

    std::chrono::high_resolution_clock::time_point before_multiplication = std::chrono::high_resolution_clock::now();

    multiply_sq_matrices(m1, m2, result, matrices_size);

    std::chrono::high_resolution_clock::time_point after_multiplication = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(after_multiplication - before_multiplication).count();
    std::cout << "Multiplication duration, seconds: " << duration << "\n";


    for (size_t i = 0; i < matrices_size; i++)
    {
        delete[] result[i];
        delete[] m1[i];
        delete[] m2[i];
    }
    delete[] result;
    delete[] m1;
    delete[] m2;

    return EXIT_SUCCESS;
}
