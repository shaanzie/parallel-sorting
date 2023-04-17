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

void merge(vector<double>& A, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for(int i = 0; i < n1; i ++) {
        L[i] = A[left + i];
    }
    for(int j = 0; j < n2; j ++) {
        R[j] = A[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            A[k] = L[i];
            i++; 
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1) {
        A[k] = L[i];
        k++;
        i++;
    }
    while(j < n2) {
        A[k] = R[j];
        k++;
        j++;
    }

}

void serial_merge_sort(vector<double>& A, int N) {

    for(int size = 1; size < N; size ++) {
        for(int left = 0; left < N - 1; left ++) {
            int mid = min(left + size - 1, N - 1);
            int right = min(left + 2*size - 1, N - 1);
            merge(A, left, mid, right);
        }
    }


}

void openmp_merge_sort(vector<double>& A, int N) {

    #pragma omp parallel for shared(A, N)
    for(int size = 1; size < N; size ++) {
        for(int left = 0; left < N - 1; left ++) {
            int mid = min(left + size - 1, N - 1);
            int right = min(left + 2*size - 1, N - 1);
            merge(A, left, mid, right);
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