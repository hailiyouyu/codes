// Quick Sort
// Solutions:
// 1. choose a pivot, and divide the array into two subarrays, let left subarray less than pivot, right subarray great than pivot
// 2. Recursively quick sort the two subarrays

// Proof of Correctness
// 1. subroutine Partition:  invariants: A[1..i] <= pivot <= A[j..n]
// 2. Induction

// Time Complexity
// T(n) = 0; n <= 1
// T(n) = T(i-1) + T(n-i) + O(n)
// Average: T(N) = O(N*lgN)
// worst: T(N) = O(N**2)

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


// Partition Algorithm
// Optimization: choose a random index between l and r as pivot, or
// choose the middle index or choose the median of the first, middle and last element.
// when input size is small, use insertion sort.

template <typename T>
int MedianOfThree(vector<T>& data, int l, int r) {
  int m = l + (r - l) / 2;
  if (data[r] < data[l])
    swap(data[r], data[l]);
  if (data[m] < data[l])
    swap(data[m], data[l]);
  if (data[r] < data[m])
    swap(data[r], data[m]);
  return m;
}

template <typename T>
int Partition(vector<T> &data, int l, int r) {
  //int pivotIndex = MedianOfThree(data, l, r);
  //  swap(data[r], data[pivotIndex]);

  T pivot = data[r];   // two special case: pivot is the largest or smallest
  int i = l-1, j = r;
  while (i < j) {
    do {
      ++i;
    } while (i < j && data[i] < pivot); // if data[i] == pivot ====> pivot is the largest
    do {
      --j;
    } while (i < j && data[j] > pivot);  // if data[j] == pivot ====> pivot is the smallest
    if (i < j)
      swap(data[i], data[j]);
  }
  swap(data[i], data[r]);
  return i;
}

template <typename T>
void QuickSort(vector<T> &data, int l, int r) {
  if (r > l) {
    int m = Partition(data, l, r);
    QuickSort(data, l, m-1);
    QuickSort(data, m+1, r);
  }
}

template <typename T>
void QuickSort(vector<T> &data) {
  int size = data.size();
  QuickSort(data, 0, size-1);
}

int main() {
  vector<int> data = {10, 1, 9, 5, 4, 7, 8, 6, 3, 2};
  QuickSort(data);
  copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';

  return 0;
}
