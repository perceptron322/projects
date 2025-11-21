#include <iostream>
#include <mpi.h>
#include <math.h>

#define EPS 0.001
#define PI 3.1415926535
#define NELEMS(x) (sizeof((x)) / sizeof((x)[0]))
#define IND(i, j) ((i) * (nx + 2) + (j))

int get_block_size(int n, int rank, int nprocs);
int get_sum_of_prev_blocks(int n, int rank, int nprocs);

int main(int argc, char *argv[])
{
    int commsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double start_time = MPI_Wtime();

    MPI_Comm cartcomm;
    int dims[2] = {0,0}, periodic[2] = {0,0};
    MPI_Dims_create(commsize, 2, dims);
    int px = dims[0];
    int py = dims[1];

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, 0, &cartcomm);
    int coords[2];
    MPI_Cart_coords(cartcomm, rank, 2, coords);
    int rankx = coords[0];
    int ranky = coords[1];

    int rows, cols;
    int args[2];
    
    if(rank == 0)
    {
        rows = 10000;
        cols = 10000;
        args[0] = rows;
        args[1] = cols;
    }
    
    MPI_Bcast(args, 2, MPI_INT, 0, cartcomm);
    rows = args[0];
    cols = args[1];

    int ny = get_block_size(rows, ranky, py);
    int nx = get_block_size(cols, rankx, px);

    double* local_grid = new double[(ny + 2) * (nx + 2)]();
    double* local_newgrid = new double[(ny + 2) * (nx + 2)]();

    double dx = 1.0 / (cols - 1.0);
    int sj = get_sum_of_prev_blocks(cols, rankx, px);

    // ИСПРАВЛЕНИЕ 1: Граничные условия только на строке 0 и ny+1 (ghost cells)
    if(ranky == 0)
    {
        for(int j = 1; j <= nx; j++)
        {
            double x = dx * (sj + j - 1);
            local_newgrid[IND(0, j)] = local_grid[IND(0, j)] = sin(PI * x);
        }
    }

    if(ranky == py - 1)
    {
        for(int j = 1; j <= nx; j++)
        {
            double x = dx * (sj + j - 1);
            local_newgrid[IND(ny + 1, j)] = local_grid[IND(ny + 1, j)] = sin(PI * x) * exp(-PI);
        }
    }

    int left, right, top, bottom;
    MPI_Cart_shift(cartcomm, 0, 1, &left, &right);
    MPI_Cart_shift(cartcomm, 1, 1, &top, &bottom);

    MPI_Datatype col;
    MPI_Type_vector(ny, 1, nx + 2, MPI_DOUBLE, &col);
    MPI_Type_commit(&col);

    MPI_Datatype row;
    MPI_Type_contiguous(nx, MPI_DOUBLE, &row);
    MPI_Type_commit(&row);

    MPI_Request reqs[8];
    int niters = 0;

    for(;;)
    {
        niters++;

        // Обмен данными
        MPI_Irecv(&local_grid[IND(0, 1)], 1, row, top, 0, cartcomm, &reqs[0]);
        MPI_Irecv(&local_grid[IND(ny + 1, 1)], 1, row, bottom, 0, cartcomm, &reqs[1]);
        MPI_Irecv(&local_grid[IND(1, 0)], 1, col, left, 0, cartcomm, &reqs[2]);
        MPI_Irecv(&local_grid[IND(1, nx + 1)], 1, col, right, 0, cartcomm, &reqs[3]);

        MPI_Isend(&local_grid[IND(1, 1)], 1, row, top, 0, cartcomm, &reqs[4]);
        MPI_Isend(&local_grid[IND(ny, 1)], 1, row, bottom, 0, cartcomm, &reqs[5]);
        MPI_Isend(&local_grid[IND(1, 1)], 1, col, left, 0, cartcomm, &reqs[6]);
        MPI_Isend(&local_grid[IND(1, nx)], 1, col, right, 0, cartcomm, &reqs[7]);

        MPI_Waitall(8, reqs, MPI_STATUSES_IGNORE);

        for(int i = 1; i <= ny; i++)
        {
            for(int j = 1; j <= nx; j++)
            {
                local_newgrid[IND(i, j)] = (
                    local_grid[IND(i - 1, j)] + local_grid[IND(i + 1, j)] + 
                    local_grid[IND(i, j - 1)] + local_grid[IND(i, j + 1)]) * 0.25;
            }
        }

        // Проверка сходимости
        double maxdiff = 0;
        for(int i = 1; i <= ny; i++)
        {
            for(int j = 1; j <= nx; j++)
            {
                maxdiff = fmax(maxdiff, fabs(local_grid[IND(i, j)] - local_newgrid[IND(i, j)]));
            }
        }

        double global_maxdiff;
        MPI_Allreduce(&maxdiff, &global_maxdiff, 1, MPI_DOUBLE, MPI_MAX, cartcomm);

        double *p = local_grid;
        local_grid = local_newgrid;
        local_newgrid = p;

        if(global_maxdiff < EPS)
            break;
    }

    double result_time = MPI_Wtime() - start_time;

    MPI_Type_free(&row);
    MPI_Type_free(&col);

    delete[] local_grid;
    delete[] local_newgrid;

    if(rank == 0)
    {
        std::cout << "# Heat 2D (mpi): grid: rows " << rows 
                << ", cols " << cols << ", procs " << commsize 
                << " (px " << px << ", py " << py 
                << "), iters " << niters << "\nTotal time: " << result_time << "." << std::endl;
    }

    MPI_Finalize();
    return 0;
}

// dop funcs
int get_block_size(int n, int rank, int nprocs)
{
    int s = n / nprocs;
    if(n % nprocs > rank)
        s++;
    return s;
}

int get_sum_of_prev_blocks(int n, int rank, int nprocs)
{
    int rem = n % nprocs;
    return n / nprocs * rank + ((rank >= rem) ? rem : rank);
}