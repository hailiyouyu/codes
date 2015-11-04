// Longest increasing subsequence of backtracking
#include <iostream>
#include <limits>
using namespace std;

int LIS(int *data, int n, int pre) {
  if (n == 0)
    return 0;
  int max = LIS(data + 1, n - 1, pre);
  if (data[0] > pre) {
    int l = 1 + LIS(data + 1, n - 1, data[0]);
    if (l > max)
      max = l;
  }
  return max;
}

int LIS(int *data, int n) {
  return LIS(data, n, numeric_limits<int>::min());
}

int main() {
  {
    int data[] = {4, 5, 1, 3, 6, 7, 2};
    cout << LIS(data, sizeof(data)/sizeof(*data)) << '\n';
  }
  {
    int data[] = {1,2,3,4,5};
    cout << LIS(data, sizeof(data)/sizeof(*data)) << '\n';
  }
  {
    int data[] = {5,4,3,2,1};
    cout << LIS(data, sizeof(data)/sizeof(*data)) << '\n';
  }
  return 0;
}
