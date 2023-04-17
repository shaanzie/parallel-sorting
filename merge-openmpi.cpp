// Author: Ishaan Lagwankar
// Course Project for CSE822
// Referred to the idea from https://computing.llnl.gov/tutorials/mpi/

// Imports
#include <bits/stdc++.h>
#include <mpi.h>
#include "merge.h"

using namespace std;

int main(int argc, char *argv[])
{

    int rank;            // Defines the rank we're on
    int size;            // Defines the size of the communicating world
    int N;               // Size of the array
    vector<double> data; // Array holder vector
    int chunksize;       // Chunk size for each process
    double start_time;   // Timer start
    double end_time;     // Timer end
    int s;               // Placeholder variable for size of array on rank 0
    int o;               // Placeholder variable for size of array coming as message
    MPI_Status status;   // Status object

    // Initializing MPI world
    MPI_Init(&argc, &argv);

    // Setting the size and ranks for processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Our size comes as an input from the bash script (bubble-submitjob.sb)
    N = stoi(argv[1]);

    // The maximum threads we're gonna allow for this process
    // Since we're doing just MPI, this value is never used, just for completeness sake
    int max_threads = stoi(argv[2]);

    // We have to initialize the array only on rank 0, other processes just get chunks
    // Master-slave approach
    if (rank == 0)
    {

        // Generate random array
        data = random_arr(N);

        // Compute chunksize
        chunksize = N / size;

        // Handle residue
        if (N % size > 0)
        {
            chunksize++;
        }

        // Pad data to match chunks, just allows me to not worry about insufficient data to be sent
        // Caused a lot of commotion about sends and recvs not ending
        for (int i = N; i < rank * chunksize; i++)
        {
            data.push_back(0);
        }
    }

    // Getting the house in order to start computation
    MPI_Barrier(MPI_COMM_WORLD);

    // Start the timer!
    start_time = MPI_Wtime();

    // Compute chunksize again, because processes don't know what the chunksize is
    // Realise this is replicating what we've done above and is bad but makes it understandable
    chunksize = N / size;

    // Handle residue
    if (N % size > 0)
    {
        chunksize++;
    }

    // Scatter chunks to all processes so they roughly get equal chunks
    // Doesn't really matter if its unequal to some processes, as we've padded the data well
    vector<double> chunk(chunksize);
    MPI_Scatter(&data[0], chunksize, MPI_DOUBLE, &chunk[0], chunksize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    data.clear();

    // Compute size of chunk and sort
    if (N >= chunksize * (rank + 1))
    {
        s = chunksize;
    }
    else
    {
        s = N - chunksize * rank;
    }
    openmp_merge_sort(chunk, s);

    // Idea: merge everything on processes with rank power of 2
    for (int step = 1; step < size; step *= 2)
    {

        // If rank is not a power of 2, we just send to the previous process as sorting is done
        if (rank % (2 * step) != 0)
        {
            MPI_Send(&chunk[0], s, MPI_DOUBLE, rank - step, 0, MPI_COMM_WORLD);
            break;
        }
        // If rank is a multiple of 2*step, we merge the chunk that we get from the previous if condition
        if (rank + step < size)
        {
            // We have to compute size of the chunk we're going to get
            if (N >= chunksize * (rank + 2 * step))
            {
                o = chunksize * step;
            }
            else
            {
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

    // End timer!
    end_time = MPI_Wtime();

    if (rank == 0)
    {

        printf("%d,%d,%d,%.10f,mpi\n", max_threads, N, size, end_time - start_time);
    }

    // Collect stuff and kill every other process
    MPI_Finalize();

    return 0;
}