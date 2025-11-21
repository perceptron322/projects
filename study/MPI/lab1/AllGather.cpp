#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int message_size = 1024;
    std::vector<int> my_message(message_size, rank * 100);
    std::vector<int> received_messages(size * message_size);
    
    std::vector<MPI_Request> send_requests(size);
    std::vector<MPI_Request> recv_requests(size);
    
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();
    
    for (int i = 0; i < size; i++) {
        MPI_Irecv(&received_messages[i * message_size], message_size, MPI_INT, i, 0, 
                  MPI_COMM_WORLD, &recv_requests[i]);
    }
    
    for (int i = 0; i < size; i++) {
        MPI_Isend(my_message.data(), message_size, MPI_INT, i, 0, 
                  MPI_COMM_WORLD, &send_requests[i]);
    }
    
    MPI_Waitall(size, send_requests.data(), MPI_STATUSES_IGNORE);
    MPI_Waitall(size, recv_requests.data(), MPI_STATUSES_IGNORE);
    
    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;
    
    std::cout << "Process " << rank << " communication time: " << elapsed_time << " seconds\n";
    
    // std::cout << "Process " << rank << " received first elements: ";
    // for (int i = 0; i < size; i++) {
    //     std::cout << received_messages[i * message_size] << " ";
    // }
    
    MPI_Finalize();
    return 0;
}
