#include <iostream>
#include <mpi.h>

// func headers
void get_chunk(int a, int b, int commsize, int rank, int *lb, int *ub);
void dgemv(float** matrix, float *b, float *c, int m, int n, int commsize, int rank);

// MAIN
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, commsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    double start_time = MPI_Wtime();

    int lb, ub, n = 100, m = 100;
    get_chunk(0, m - 1, commsize, rank, &lb, &ub);
    int nrows = ub - lb + 1;

    // init matrix and vectors
    float** matrix = new float*[nrows];
    for(int i = 0; i < nrows; i++)
        matrix[i] = new float[n];

    float* b = new float[n];
    float* c = new float[m];

    for(int i = 0; i < m; i++)
        c[i] = 0.0;

    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = lb + i + j;
        }
    }

    for(int i = 0; i < n; i++)
        b[i] = i + 1;

    // computing the parts of vector c
    dgemv(matrix, b, c, m, n, commsize, rank);

    int* recvcounts = new int[commsize];
    int* displs = new int[commsize];
    
    for(int i = 0; i < commsize; i++)
    {
        int lb_i, ub_i;
        get_chunk(0, m - 1, commsize, i, &lb_i, &ub_i);
        recvcounts[i] = ub_i - lb_i + 1;
        displs[i] = lb_i;
    }

    float* c_gathered = new float[m];
    for(int i = 0; i < m; i++)
        c_gathered[i] = 0.0;

    MPI_Allgatherv(&c[lb], nrows, MPI_FLOAT,
                   c_gathered, recvcounts, displs, MPI_FLOAT,
                   MPI_COMM_WORLD);

    for(int i = 0; i < m; i++)
        c[i] = c_gathered[i];

    // check result
    if(rank == 0)
    {
        double res_time = MPI_Wtime() - start_time;
        std::cout << "Result vector c (first 5 elements):\n";
        for(int i = 0; i < 5 && i < m; i++)
        {
            std::cout << "c[" << i << "] = " << c[i] << "\n";
        }

        std::cout << "\nResult Time: " << res_time << "\n";
    }

    for(int i = 0; i < nrows; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] b;
    delete[] c;
    delete[] c_gathered;
    delete[] recvcounts;
    delete[] displs;

    MPI_Finalize();
    return 0;
}

// dop funcs
void get_chunk(int a, int b, int commsize, int rank, int *lb, int *ub)
{
    int n = b - a + 1;
    int q = n / commsize;
    if(n % commsize) q++;
    int r = q * commsize - n;

    int chunk = q;
    if(rank >= commsize - r) chunk = q - 1;

    *lb = a;
    if(rank > 0)
    {
        if(rank <= commsize - r)
        {
            *lb = q * rank;
        } else 
        {
            *lb = q * (commsize - r) + (q - 1) * (rank - (commsize - r));
        }
    }

    *ub = *lb + chunk - 1;
}

void dgemv(float** matrix, float *b, float *c, int m, int n, int commsize, int rank)
{
    int lb, ub;
    get_chunk(0, m - 1, commsize, rank, &lb, &ub);
    int nrows = ub - lb + 1;

    for(int i = 0; i < nrows; i++)
    {
        c[lb + i] = 0.0;

        for(int j = 0; j < n; j++)
        {
            c[lb + i] += matrix[i][j] * b[j];
        }
    }
}
