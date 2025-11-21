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
    std::vector<char> temp_buf(count);
    if(rank == 0)
    {
        rbuf.resize(count * comsize);
    }

    double start_time, end_time;
    
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    if(rank == 0)
    {
        for(int i = 1; i < comsize; i++)
        {
            MPI_Recv(temp_buf.data(), count * comsize, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int j = 0; j < count; j++)
            {
                rbuf[i * count + j] = temp_buf[j];
            }
        }
    } else {
        MPI_Send(sbuf.data(), count, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    end_time = MPI_Wtime();

    if(rank == 0)
    {
        // for(char c : rbuf) printf("%c", c);
        // printf("\n");
        printf("Proccess: %d. Time: %.6f seconds\n", rank, end_time - start_time);
    } else {
        printf("Proccess: %d. Time: %.6f seconds\n", rank, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}