#include <iostream>
#include <cmath>
#include <mpi.h>

double f(double x)
    {
        return x*x*x*x / (0.5*x*x + x + 6);
    }


int main(int argc, char* argv[])
{
    // 29 variant: f(x) = x^4 / (0.5x^2 + x + 6),  a = 0.4,  b = 1.5.

    const double eps = 1E-6;
    const int n0 = 100;
    double a = 0.4, b = 1.5;

    int commsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int k, n = n0;
    double sq[2], delta = 1;

    double start_time = 0.0, result_time = 0.0;
    if(rank == 0)
        start_time = MPI_Wtime();


    for(k = 0; delta > eps; n *= 2, k ^= 1)
    {
        int points_per_proc = n / commsize;
        int lb = rank * points_per_proc;
        int ub = (rank == commsize - 1) ? (n-1) : (lb + points_per_proc - 1);
        double h = (b - a) / n;
        double sum = 0.0;

        for(int i = lb; i <= ub; i++)
            sum += f(a + h * (i + 0.5));

        MPI_Allreduce(&sum, &sq[k], 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        sq[k] *= h;

        if(n > n0)
            delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
    }


    if(rank == 0)
    {
        result_time = MPI_Wtime() - start_time;
        printf("Processes count : %d.\nResult : %.12f\n", commsize, sq[k]);
        std::cout << "Result time : " << result_time << "\n";
    }


    MPI_Finalize();
    return 0;
}