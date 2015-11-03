#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void RecursiveNQueens(vector<int>& res, int i, int n) {
    if (i == n) {
        for (auto e : res)
            cout << e << ' ';
        cout << '\n';
        return;
    }
    int j, k;
    for (j = 0; j < n; ++j) {
        bool legal = true;
        for (k = 0; k < i; ++k)
            if (res[k] == j || res[k] == j - i + k || res[k] == i + j - k)
                legal = false;
        if (legal) {
            res[i] = j;
            RecursiveNQueens(res, i + 1, n);
        }
    }
}

void RecursiveNQueens(int n) {
    vector<int> res(n, -1);
    RecursiveNQueens(res, 0, n);
}

int main() {
    int n;
    cout << "input number of Queens: ";
    cin >> n;
    cout << "\nOne Solution: \n";
    assert(n != 2 && n != 3);
    RecursiveNQueens(n);
    return 0;
}
