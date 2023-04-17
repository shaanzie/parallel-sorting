#include <bits/stdc++.h>

using namespace std;

vector<int> random_arr(int N)
{

    srand(0xFEEDFACE);

    vector<int> A;

    for (size_t i = 0; i < N; i++)
    {

        int num = fmod((int)rand(), 20);
        A.push_back(num);
    }

    return A;
}

void serial_quick_sort(vector<int> &A, int start, int end)
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
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }
    quicksort(A, start, j);
    quicksort(A, i, end);
}

void openmp_quick_sort(vector<int> &A, int start, int end)
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
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }
#pragma omp task
    quicksort(A, start, j);
#pragma omp task
    quicksort(A, i, end);
}

void print_vector(vector<int> &A)
{
    for (auto i : A)
    {
        cout << i << " ";
    }
    cout << endl;
}