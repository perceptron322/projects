#include <mpi.h>
#include <iostream>
#include <cstdio>
#include <vector>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int comsize, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &comsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int count = 1024;
    std::vector<char> sbuf(count, 'A');
    std::vector<char> rbuf(count);

    // Измерение времени начинается
    double start_time = MPI_Wtime();

    if(rank == 0)
    {
        for(int i = 1; i < comsize; i++)
        {
            MPI_Send(sbuf.data(), count, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(rbuf.data(), count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Измерение времени заканчивается
    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;

    // if(rank != 0)
    // {
    //     printf("Process %d has message: ", rank);
    //     for(int i = 0; i < count; i++) printf("%c", rbuf[i]);
    //     printf("\n");
    // }

    // Вывод времени для каждого процесса
    printf("Process %d communication time: %.6f seconds\n", rank, elapsed_time);

    MPI_Finalize();
    return 0;
}