// Quick Select: select the kth smallest element in unsorted array

// Use Partition of Quick Sort:
// 1. select a pivot, and divide the array into two subarray, return index i of pivot
// 2. compares k and i, we can elimate one subarray.
// 3. Quick Select in the other subarray

// Time Complexity
// T(n) <= max(max{T(r-1), T(n-r)} + O(n))
// Average: O(N)   Worst: O(N**2)

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
int Partition(vector<T> &data, int l, int r) {
  T pivot = data[r];
  int i = l-1, j = r;
  while (i < j) {
    do {
      ++i;
    } while (i < j && data[i] < pivot);
    do {
      --j;
    } while (i < j && data[j] > pivot);
    if (i < j)
      swap(data[i], data[j]);
  }
  swap(data[i], data[r]);
  return i;
}

template <typename T>
T QuickSelection(vector<T> &data, int l, int r, int k) {
  if (l == r)
    return data[l];
  int p = Partition(data, l, r);
  if (k < p)
    return QuickSelection(data, l, p-1, k);
  else if (k > p)
    return QuickSelection(data, p+1, r, k);
  else
    return data[p];
}

int main() {
  srand(time(NULL));
  vector<int> data;

  for (int i = 0; i < 10; ++i) {
    data.push_back(rand() % 100);
  }

  vector<int> tmp(data);
  sort(tmp.begin(), tmp.end());
  copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';

  for (int i = 0; i < data.size(); ++i) {
    cout << "Element " << i << " is: " << QuickSelection(data, 0, data.size()-1, i) << '\n';
  }
  return 0;
}
