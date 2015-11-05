#include <iostream>
#include <vector>
using namespace std;

// Fn = Fn-1 + Fn-2, n >= 2
// F0 = 0, F1 = 1

// Recursively Solution
// T(n) = O(1.618^n)
int RecFibo(int n) {
  if (n < 2)
    return n;
  return RecFibo(n-1) + RecFibo(n-2);
}

int MemFibo(vector<int>& m, int n) {
  if (n < 2) {
    m[n] = n;
    return n;
  }
  if (m[n] != -1)
    return m[n];
  int partial = MemFibo(m, n-1) + MemFibo(m, n-2);
  m[n] = partial;
  return partial;
}

int MemFibo(int n) {
  vector<int> m(n+1, -1);
  return MemFibo(m, n);
}

int IterFibo(int n) {
  if (n < 2)
    return n;
  vector<int> f(n+1);
  f[0] = 0;
  f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    f[i] = f[i-1] + f[i-2];
  }
  return f[n];
}

int IterFibo2(int n) {
  if (n < 2)
    return n;
  int first = 0, second = 1;
  for (int i = 2; i <= n; ++i) {
    int tmp = first + second;
    first = second;
    second = tmp;
  }
  return second;
}

int main() {
  {
    for (int i = 0; i < 20; ++i)
      cout << RecFibo(i) << ' ';
    cout << '\n';
  }
  {
    for (int i = 0; i < 20; ++i)
      cout << MemFibo(i) << ' ';
    cout << '\n';
  }
  {
    for (int i = 0; i < 20; ++i)
      cout << IterFibo2(i) << ' ';
    cout << '\n';
  }

  return 0;
}
