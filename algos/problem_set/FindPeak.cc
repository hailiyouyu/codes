// Peak: A[i] > A[i-1] && A[i] > A[i+1]
// Time Complexity : O(lgn)
#include <iostream>
#include <vector>
using namespace std;

namespace {
  int FindPeak(vector<int>& data) {
    int l = 0, r = data.size() - 1, m;
    while (l <= r) {
      m = l + (r - l) / 2;
      if ((m == 0 || data[m] >= data[m-1]) && (m == data.size() - 1 || data[m] >= data[m+1]))
        return data[m];
      else if (data[m] < data[m+1])
        l = m + 1;
      else
        r = m - 1;
    }
    return -1;
  }
}

int main() {
  {
    vector<int> data = {1};
    cout << FindPeak(data) << '\n';
  }
  {
    vector<int> data = {1, 2, 3};
    cout << FindPeak(data) << '\n';
  }
  {
    vector<int> data = {4, 3, 2, 1};
    cout << FindPeak(data) << '\n';
  }
  {
    vector<int> data = {1, 3, 20, 4, 1, 0};
    cout << FindPeak(data) << '\n';
  }
  {
    vector<int> data = {0, 1};
    cout << FindPeak(data) << '\n';
  }
  {
    vector<int> data = {1, 0};
    cout << FindPeak(data) << '\n';
  }
  return 0;
}
