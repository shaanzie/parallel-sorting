#include <bits/stdc++.h>

using namespace std;

vector<int> random_arr(int N) {

    srand(0xFEEDFACE);

    vector<int> A;

    for (size_t i = 0; i < N; i++){

        int num = fmod((int)rand(), 20);
        A.push_back(num);
    }

    return A;

}

int pivot_element(vector<int>& A, int l, int h) {

    int x = A[h];
    int i = l - 1;

    for(int j = l; j <= h; j ++) {
        if(A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[h]);
    return i + 1;

}

void serial_quick_sort(vector<int>& A, int N) {

    stack<int> aux;

    aux.push(0);
    aux.push(N - 1);

    while(!aux.empty()) {
        int h = aux.top();
        aux.pop();
        int l = aux.top();
        aux.pop();

        int p = pivot_element(A, l, h);

        if(p - 1 > l) {
            aux.push(l);
            aux.push(p - 1);
        }

        if(p + 1 < h) {
            aux.push(p + 1);
            aux.push(h);
        }
    }

}

void print_vector(vector<int>& A) {
    for(auto i : A) {
        cout << i << " ";
    }
    cout << endl;
}