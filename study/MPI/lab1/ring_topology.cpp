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

    std::vector<char> my_message(count, static_cast<char>(rank));
    std::vector<char> tbuf(count);
    std::vector<std::vector<char>> all_messages(comsize, std::vector<char>(count));
    all_messages[rank] = my_message;

    int prev_rank = (rank + comsize - 1) % comsize;
    int next_rank = (rank + 1) % comsize;

    std::vector<char> message_to_send = my_message;

    // Измерение времени начинается
    double start_time = 0.0, end_time = 0.0;
    if(rank == 0) {
        start_time = MPI_Wtime();
    }

    for(int i = 0; i < comsize - 1; i++)
    {
        MPI_Sendrecv(message_to_send.data(), count, MPI_CHAR, next_rank, 0, tbuf.data(), count, MPI_CHAR, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        all_messages[(rank + comsize - i - 1) % comsize] = tbuf;
        message_to_send = tbuf;
    }

    // Измерение времени заканчивается
    if(rank == 0) {
        end_time = MPI_Wtime();
        printf("Communication time: %.6f seconds\n", end_time - start_time);
    }

    // printf("Process %d has messages:", rank);
    // for(int i = 0; i < static_cast<int>(all_messages.size()); i++)
    // {
    //     printf(" [");
    //     for(int j = 0; j < count; j++)
    //     {
    //         printf("%d", static_cast<int>(all_messages[i][j]));
    //         if(j < count - 1) printf(",");
    //     }
    //     printf("],");
    // }
    printf("\n");

    MPI_Finalize();
    return 0;
}