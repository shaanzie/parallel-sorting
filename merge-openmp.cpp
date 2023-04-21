#include <bits/stdc++.h>
#include <omp.h>
#include "merge.h"

using namespace std;

int main(int argc, char *argv[])
{

    int N = stoi(argv[1]);            // Size of the array to be sorted
    int rounds = 10;                  // Number of rounds we want to do
    int max_threads = stoi(argv[2]);  // Maximum threads we're gonna allow
    int procs = stoi(argv[3]);        // Maximum number of processes we're gonna allow; Doesn't matter here
    omp_set_num_threads(max_threads); // Setting the environment variables
    double start, end, total;         // Timers

    // Generate a random array of doubles
    vector<double> A = random_arr(N);
    vector<double> B = A;
    stable_sort(B.begin(), B.end());

    for (int i = 0; i < rounds; i++)
    {

        // Start timer!
        start = omp_get_wtime();

        // Call our sorting function
        openmp_merge_sort(A, 0, A.size());

        // Stop timer!
        end = omp_get_wtime();

        // if (B != A)
        // {
        //     cout << "Verification failed!" << endl;
        // }
        total += end - start;
    }

    printf("%d,%d,%d,%.10f,openmp\n", max_threads, N, procs, total / rounds);

    return 0;
}