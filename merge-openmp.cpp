#include <bits/stdc++.h>
#include <omp.h>
#include "merge.h"

using namespace std;

int main(int argc, char* argv[]) {

    int N = stoi(argv[1]);
    int rounds = 10;
    int max_threads = stoi(argv[2]);
    omp_set_num_threads(max_threads);
    double start, end, total;

    vector<double> A = random_arr(N);

    for(int i = 0; i < rounds; i++) {
        start = omp_get_wtime();
        openmp_merge_sort(A, A.size());
        end = omp_get_wtime();

        total += end - start;

    }   
    
    printf("%d,%d,%d,%.10f,openmp\n", max_threads, N, 1, total / rounds);

    return 0;


}