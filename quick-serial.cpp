#include <bits/stdc++.h>
#include <omp.h>
#include "quick.h"

using namespace std;

int main(int argc, char* argv[]) {

    int N = stoi(argv[1]);
    int rounds = 10;
    double start, end, total;

    vector<int> A = random_arr(N);

    for(int i = 0; i < rounds; i++) {
        start = omp_get_wtime();
        serial_quick_sort(A, A.size());
        end = omp_get_wtime();

        total += end - start;

    }

    print_vector(A);

    printf("%d,%d,%d,%.10f,serial\n", 1, N, 1, total / rounds);

    return 0;


}