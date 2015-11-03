#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

int MedianOfFive(vector<int>& data, int l, int r) {
  sort(data.begin() + l, data.begin() + r + 1);
  return data[l + (r - l + 1) / 2];
}

int Partition(vector<int>& data, int l, int r, int pivot) {
  int i, j;
  for (i = l; i <= r; ++i)
    if (data[i] == pivot)
      break;
  using std::swap;
  swap(data[i], data[r]);
  i = l - 1;
  j = r;
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

int MedianOfMedians(vector<int>& data, int l, int r, int k) {
  if (l == r)
    return data[l];
  vector<int> group;
  for (int i = l; i <= r; i += 5) {
    int group_right = i + 4;
    if (group_right > r)
      group_right = r;
    int median = MedianOfFive(data, i, group_right);
    group.push_back(median);
  }
  int pivot = MedianOfMedians(group, 0, group.size()-1, group.size()/2);
  int pivot_index = Partition(data, l, r, pivot);
  if (pivot_index == k)
    return data[k];
  else if (pivot_index > k)
    return MedianOfMedians(data, l, pivot_index-1, k);
  else
    return MedianOfMedians(data, pivot_index+1, r, k);
}

int MedianOfMedians(vector<int>& data, int k) {
  assert(k >= 0 && k < data.size());
  return MedianOfMedians(data, 0, data.size()-1, k);
}
/*
int main() {
  {
    vector<int> data = {10, 15, 13, 9, 6, 12, 20, 11};
    cout << MedianOfMedians(data, data.size() / 2) << '\n';
  }
  {
    vector<int> data = {13, 24, 11, 9, 7, 4, 6, 10, 12};
    cout << MedianOfMedians(data, data.size() / 2) << '\n';
  }
  return 0;
}
*/
