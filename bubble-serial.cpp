#include <bits/stdc++.h>
#include <omp.h>
#include "bubble.h"

using namespace std;

int main(int argc, char* argv[]) {

    int N = stoi(argv[1]);
    int max_threads = stoi(argv[2]);
    int procs = stoi(argv[3]);
    int rounds = 10;
    double start, end, total;

    vector<double> A = random_arr(N);

    for(int i = 0; i < rounds; i++) {
        start = omp_get_wtime();
        serial_bubble_sort(A, A.size());
        end = omp_get_wtime();

        total += end - start;

    }

    printf("%d,%d,%d,%.10f,serial\n", max_threads, N, procs, total / rounds);

    return 0;


}