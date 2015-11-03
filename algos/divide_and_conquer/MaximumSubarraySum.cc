// Maximum Subarray Sum
// Divide and Conquer
// O(nlgn)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MaximumSum(vector<int>& data, int l, int r) {
  if (l == r)
    return data[l];
  int m = l + (r - l) / 2;
  int left_sum = MaximumSum(data, l, m);
  int right_sum = MaximumSum(data, m+1, r);

  int i = m, j = m+1;
  int left_middle = data[i], right_middle = data[j];
  int tmp_sum = 0;
  for (; i >= l; --i) {
    tmp_sum += data[i];
    if (tmp_sum > left_middle)
      left_middle = tmp_sum;
  }
  tmp_sum = 0;
  for (; j <= r; ++j) {
    tmp_sum += data[j];
    if (tmp_sum > right_middle)
      right_middle = tmp_sum;
  }
  return max({left_sum, right_sum, left_middle+right_middle});
}
int MaximumSum(vector<int>& data) {
  return MaximumSum(data, 0, data.size()-1);
}

int main() {
  {
    vector<int> data = {-2, -5, 6, -2, -3, 1, 5, -6};
    cout << MaximumSum(data) << '\n';
  }
  {
    vector<int> data = {2, 3, 4, 5, 7};
    cout << MaximumSum(data) << '\n';
  }
  {
    vector<int> data = {-1, -2, -3, 0};
    cout << MaximumSum(data) << '\n';
  }
  return 0;
}
