#include <bits/stdc++.h>

using namespace std;

vector<double> random_arr(int N) {

    srand(0xFEEDFACE);

    vector<double> A;

    for (size_t i = 0; i < N; i++){

        double num = fmod((double)rand(), 20);
        A.push_back(num);
    }

    return A;

}

void serial_bubble_sort(vector<double>& A, int N) {

    int i, j;

    for (i = 0; i < N - 1; i++)
 
        for (j = 0; j < N - i - 1; j++)

            if (A[j] > A[j + 1])

                swap(A[j], A[j + 1]);

}


void openmp_bubble_sort(vector<double>& A, int N) {

    #pragma omp parallel default(none) shared(A, N) 
    {
        for(int block = 0; block < N; block++) {
            if(block % 2 == 0) {
                #pragma omp for
                for(int i = 1; i < N; i += 2) {
                    if(A[i] > A[i-1])
                        swap(A[i], A[i-1]);
                }
            }
            else {
                #pragma omp for
                for(int i = 1; i < N - 1; i += 2) {
                    if(A[i] > A[i-1])
                        swap(A[i], A[i-1]);
                }
            }
        }

    }

}

vector<double> merge(vector<double>& A, int M, vector<double>& B, int N) {

    vector<double> result = vector<double>(N + M, 0);
    int i = 0, j = 0;

    for(int k = 0; k < N + M; k++) {

        if(i >= M) {
            result[k] = B[j];
            j++;
        }
        else if(j >= N) {
            result[k] = A[i];
            i++;
        }
        else if(A[i] < B[j]) {
            result[k] = A[i];
            i++;
        }
        else {
            result[k] = B[j];
            j++;
        }
    }

    return result;


}

void print_vector(vector<double>& A) {
    for(auto i : A) {
        cout << i << " ";
    }
    cout << endl;
}