// Referred to the idea from https://computing.llnl.gov/tutorials/mpi/
#include <bits/stdc++.h>
#include <mpi.h>
#include "bubble.h"

using namespace std;

int main(int argc, char *argv[]) {

    int rank;
    int size;
    int N;
    vector<double> data;
    int chunksize;
    double start_time;
    double end_time;
    int s;
    int o;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    N = stoi(argv[1]);
    int max_threads = stoi(argv[2]);

    if(rank == 0) {

        // Generate random array
        data = random_arr(N);

        // Compute chunksize
        chunksize = N / size;
        // Handle residue
        if(N % size > 0) {
            chunksize++;
        }

        // Pad data to match chunks
        for(int  i = N; i < rank * chunksize; i++) {
            data.push_back(0);
        }

    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    // Compute chunksize
    chunksize = N / size;
    // Handle residue
    if(N % size > 0) {
        chunksize++;
    }

    // Scatter chunks to all processes so they roughly get equal chunks
    vector<double> chunk(chunksize);
    MPI_Scatter(&data[0], chunksize, MPI_DOUBLE, &chunk[0], chunksize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    data.clear();

    // Compute size of chunk and sort
    if(N >= chunksize * (rank + 1)) {
        s = chunksize;
    }
    else {
        s = N - chunksize * rank;
    }
    serial_bubble_sort(chunk, s);

    // Idea: merge everything on processes with rank power of 2
    for(int step = 1; step < size; step *= 2) {

        // If rank is not a power of 2, we just send to the previous process as sorting is done
        if(rank % (2*step) != 0) {
            MPI_Send(&chunk[0], s, MPI_DOUBLE, rank - step, 0, MPI_COMM_WORLD);
            break;
        }
        // If rank is a multiple of 2*step, we merge the chunk that we get from the previous if condition
        if(rank + step < size) {
            // We have to compute size of the chunk we're going to get
            if(N >= chunksize * (rank + 2*step)) {
                o = chunksize * step;
            }
            else {
                o = N - chunksize * (rank + step);
            }
            // Make space for the chunk to come in
            vector<double> other(o);
            MPI_Recv(&other[0], o, MPI_DOUBLE, rank + step, 0, MPI_COMM_WORLD, &status);

            // Merge the data coming in from the data we have
            data = merge(chunk, s, other, o);

            chunk = data;
            s = s + o;
        }
    }

    end_time = MPI_Wtime();

    if(rank == 0) {

        printf("%d,%d,%d,%.10f,mpi\n", max_threads, N, size, end_time - start_time);
    }

    MPI_Finalize();

    return 0;

}