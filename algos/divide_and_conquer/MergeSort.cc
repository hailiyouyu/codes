// Merge Sort
// Solutions:
// 1. divide the input array into two subarrays of roughly equal size
// 2. recursively mergesort each of the subarrays
// 3. merge the two subarrays into a single sorted array

// Proof of Correctness
// 1. n <= 1, nothing to do, the array is sorted
// 2. n > 1, from induction hypothesis: the two subarrays are sorted correctly, A[1..m], A[m+1..n];
// 3. prove merge works fine.

// Time Complexity:
// T(1) = 0
// T(n) = 2*T(n/2) + O(n)
// ==> T(n) = O(n*lg(n))

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template <typename T>
void Merge(vector<T> &data, int l, int m, int r) {
  vector<T> left, right;
  for (int i = l; i <=m; ++i)
    left.push_back(data[i]);
  for (int i = m+1; i <=r; ++i)
    right.push_back(data[i]);

  int k = l, i = 0, j = 0;
  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j])
      data[k++] = left[i++];
    else
      data[k++] = right[j++];
  }
  while (i < left.size())
    data[k++] = left[i++];
  while (j < right.size())
    data[k++] = right[j++];
}

template <typename T>
void MergeSort(vector<T> &data, int l, int r) {
  if (r > l) {
    int m = l + (r-l) / 2;
    MergeSort(data, l, m);
    MergeSort(data, m+1, r);
    Merge(data, l, m, r);
  }
}

template <typename T>
void MergeSort(vector<T> &data) {
  int n = data.size();
  MergeSort(data, 0, n-1);
}


int main() {
  vector<int> data = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  MergeSort(data);

  copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';

  return 0;
}
