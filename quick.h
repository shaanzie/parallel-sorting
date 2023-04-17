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

void serial_quick_sort(vector<double> &A, int start, int end)
{
    if (start >= end)
        return;
    int pivot = A[(start + end) / 2];
    int i = start;
    int j = end;
    while (i <= j)
    {
        while (A[i] < pivot)
            i++;
        while (A[j] > pivot)
            j--;
        if (i <= j)
        {
            double temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }
    serial_quick_sort(A, start, j);
    serial_quick_sort(A, i, end);
}

void openmp_quick_sort(vector<double> &A, int start, int end)
{
    if (start >= end)
        return;
    int pivot = A[(start + end) / 2];
    int i = start;
    int j = end;
    while (i <= j)
    {
        while (A[i] < pivot)
            i++;
        while (A[j] > pivot)
            j--;
        if (i <= j)
        {
            double temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }
#pragma omp task
    openmp_quick_sort(A, start, j);
#pragma omp task
    openmp_quick_sort(A, i, end);
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

void print_vector(vector<int> &A)
{
    for (auto i : A)
    {
        cout << i << " ";
    }
    cout << endl;
}