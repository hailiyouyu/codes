// Give a sorted array, find A[i] == i
// Time Complexity: O(lgn)

#include <iostream>
#include <vector>

using namespace std;

namespace {
  int Find(vector<int>& data) {
    int l = 0, r = data.size() - 1, m;
    while (l <= r) {
      m = l + (r - l) / 2;
      if (data[m] == m)
        return m;
      else if (data[m] < m)
        l = m + 1;
      else
        r = m - 1;
    }
    return -1;
  }
}

int main() {
  {
    vector<int> data = {-10, -5, 0, 3, 7};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {0, 2, 5, 8, 17};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {-10, -5, 3, 4, 7, 9};
    cout << Find(data) << '\n';
  }
  return 0;
}
