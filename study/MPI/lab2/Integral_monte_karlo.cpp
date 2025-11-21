#include <iostream>
#include <cmath>
#include <mpi.h>
#include <cstdlib>
#include <ctime>

double f(double x, double y)
{
    return exp(x - y);
}

double getrand()
{
    return (double)rand() / RAND_MAX;
}

const int n = 10000000;

int main(int argc, char* argv[])
{
    int commsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL) + rank);

    double sum = 0.0;

    double start_time = MPI_Wtime();

    for(int i = rank; i < n; i += commsize)
    {
        double x = -1.0 + getrand();  // x in [-1, 0]
        double y = getrand();          // y in [0, 1]
        
        sum += f(x, y);
    }

    double global_sum = 0.0;
    MPI_Reduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        double result = global_sum / n;
        
        double res_time = MPI_Wtime() - start_time;
        printf("Result : %.12f\n", result);
        printf("Dots : %d\n", n);
        printf("Time : %.12f\n", res_time);
    }

    MPI_Finalize();
    return 0;
}