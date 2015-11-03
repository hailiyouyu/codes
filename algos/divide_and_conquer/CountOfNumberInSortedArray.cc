#include <iostream>
#include <vector>

using namespace std;

int BinarySearchFirst(vector<int>& data, int x) {
  int l, m, r;
  l = 0;
  r = data.size()-1;
  while (l <= r) {
    m = l + (r-l)/2;
    if (data[m] == x && (m == 0 || data[m-1] < x))
      return m;
    else if (x > data[m])
      l = m+1;
    else
      r = m-1;
  }
  return -1;
}

int BinarySearchLast(vector<int>& data, int x) {
  int l = 0, r = data.size()-1, m;
  while (l <= r) {
    m = l + (r-l)/2;
    if (x == data[m] && (m == data.size()-1 || x < data[m+1]))
      return m;
    else if (x  < data[m])
      r = m-1;
    else
      l = m+1;
  }
  return -1;
}

int NumberOfSotedArray(vector<int>& data, int x) {
  int first, last;
  if ((first = BinarySearchFirst(data, x)) == -1)
    return 0;
  if ((last = BinarySearchLast(data, x)) == -1)
    return 0;
  return last - first + 1;
}

int main() {
  {
    vector<int> data = {1, 1, 2, 2, 2, 2, 3};
    cout << NumberOfSotedArray(data, 2) << '\n';
  }
  {
    vector<int> data = {1, 1, 2, 2, 2, 2, 3};
    cout << NumberOfSotedArray(data, 3) << '\n';
  }
  {
    vector<int> data = {1, 1, 2, 2, 2, 2, 3};
    cout << NumberOfSotedArray(data, 1) << '\n';
  }
  {
    vector<int> data = {1, 1, 2, 2, 2, 2, 3};
    cout << NumberOfSotedArray(data, 4) << '\n';
  }
  return 0;
}
