// give an array, whose element first increasing then decreasing, find the maximum element
// Time Complexity : O(lgn)
// NOT WORK FOR DUPLICATE ELEMENTS
#include <iostream>
#include <vector>
using namespace std;

namespace {
  int Find(vector<int>& data) {
    int l = 0, r = data.size() - 1, m;
    while (l <= r) {
      m = l + (r - l) / 2;
      if (m == 0) {
        if (data[m] > data[m+1])
          return data[m];
        else
          l = m + 1;
      }
      else if (m == data.size() - 1) {
        if (data[m] > data[m-1])
          return data[m];
        else
          r = m - 1;
      } else if (data[m] > data[m-1] && data[m] > data[m+1]) {
        return data[m];
      } else if (data[m] < data[m+1]) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    return -1;
  }
}

int main() {
  {
    vector<int> data = {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {1, 3, 50, 10, 9, 7, 6};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {10, 20, 30, 40, 50};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {120, 100, 80, 20, 0};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {1, 2};
    cout << Find(data) << '\n';
  }
  {
    vector<int> data = {2, 1};
    cout << Find(data) << '\n';
  }
  //{
  //vector<int> data = {0, 1, 1, 2, 2, 2, 2, 2, 3, 4, 4, 5, 3, 3, 2, 2, 1, 1};
  //cout << Find(data) << '\n';
  //}

  return 0;
}
