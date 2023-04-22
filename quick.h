#include <bits/stdc++.h>

using namespace std;

vector<double> random_arr(int N)
{

    srand(0xFEEDFACE);

    vector<double> A;

    for (size_t i = 0; i < N; i++)
    {

        double num = fmod((double)rand(), 20);
        A.push_back(num);
    }

    return A;
}

int partition(vector<double> &A, int low, int high)
{

    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (A[j] <= pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return i + 1;
}

void serial_quick_sort(vector<double> &A, int start, int end)
{
    if (start < end)
    {
        int p = partition(A, start, end);
        serial_quick_sort(A, start, p - 1);
        serial_quick_sort(A, p + 1, end);
    }
}

void openmp_quick_sort(vector<double> &A, int start, int end)
{
    if (start < end)
    {
        int p = partition(A, start, end);

#pragma omp parallel sections
        {
#pragma omp section
            {
                openmp_quick_sort(A, start, p - 1);
            }
#pragma omp section
            {
                openmp_quick_sort(A, p + 1, end);
            }
        }
    }
}

vector<double> merge(vector<double> &A, int M, vector<double> &B, int N)
{

    vector<double> result = vector<double>(N + M, 0);
    int i = 0, j = 0;

    for (int k = 0; k < N + M; k++)
    {

        if (i >= M)
        {
            result[k] = B[j];
            j++;
        }
        else if (j >= N)
        {
            result[k] = A[i];
            i++;
        }
        else if (A[i] < B[j])
        {
            result[k] = A[i];
            i++;
        }
        else
        {
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