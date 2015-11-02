#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <limits>
using namespace std;

extern int MedianOfMedians(vector<int>&, int, int, int);
extern int Partition(vector<int>&, int, int, int);

int DisLesser(vector<int>& data, int l, int r, int m, int d) {
  for (int i = l; i <= r; ++i) {
    if (abs(data[i] - data[m]) < d)
      return abs(data[i] - data[m]);
  }
  return numeric_limits<int>::max();
}
int ClosestDis(vector<int>& data, int l, int r) {
  if (l > r) {
    cout << "ERROR\n";
    exit(1);
  }
  if (l == r)
    return numeric_limits<int>::max();
  if (l + 1 == r)
    return abs(data[l] - data[r]);
  
  int median = MedianOfMedians(data, l, r, l + (r - l + 1) / 2);
  int m = Partition(data, l, r, median);

  int left_distance = ClosestDis(data, l, m-1);
  int right_distance = ClosestDis(data, m+1, r);

  int minor = min(left_distance, right_distance);
  int left_middle = DisLesser(data, l, m-1, m, minor);
  int right_middle = DisLesser(data, m+1, r, m, minor);

  return min({minor, left_middle, right_middle});
}
int ClosestDis(vector<int>& data) {
  return ClosestDis(data, 0, data.size() - 1);
}

void Shuffle(vector<int>& data) {
  srand(time(0));  
  for (int i = data.size()-1; i > 0; --i) {
    int j = rand() % i;
    using std::swap;
    swap(data[i], data[j]);
  }
}

int main() {
  srand(time(0));
  vector<int> data;
  for (int i = 0; i < 20; ++i)
    data.push_back(rand() % 50);

  sort(data.begin(), data.end());
  auto last = unique(data.begin(), data.end());
  data.erase(last, data.end());

  copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';
  Shuffle(data);
  copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';
  cout << ClosestDis(data) << '\n';

  {
    cout << "!!!\n";
    vector<int> val = {10, 7, 18, 20, 15, 12};
    cout << ClosestDis(val) << '\n';
  }
  return 0;
}
