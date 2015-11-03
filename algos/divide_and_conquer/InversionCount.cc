#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <algorithm>
using namespace std;


void InvertCount(vector<int>& data, int low, int high, int& count);
void Merge(vector<int>& data, int l, int m, int r, int& count);


int InvertCount(vector<int> data) {
  int count = 0;
  InvertCount(data, 0, data.size()-1, count);
  return count;
}

void InvertCount(vector<int>& data, int low, int high, int& count) {
  if (low < high) {
    int m = low + (high - low) / 2;
    InvertCount(data, low, m, count);
    InvertCount(data, m+1, high, count);
    Merge(data, low, m, high, count);
  }
}

void Merge(vector<int>& data, int l, int m, int r, int& count) {
  vector<int> left, right;
  for (int i = l; i <= m; ++i)
    left.push_back(data[i]);
  for (int i = m+1; i <= r; ++i)
    right.push_back(data[i]);
  int i, j, k;
  i = j = 0;
  k = l;
  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j])
      data[k++] = left[i++];
    else {
      data[k++] = right[j++];
      count += left.size()-i;
    }
  }
  while (i < left.size()) {
    data[k++] = left[i++];
  }
  while (j < right.size()) {
    data[k++] = right[j++];
  }
}

int BruteForce(vector<int>& data) {
  int count = 0;
  for (int i = 0; i < data.size()-1; ++i)
    for (int j = i+1; j < data.size(); ++j)
      if (data[i] > data[j])
        ++count;
  return count;
}

int main() {
  vector<int> data;
  srand(time(0));
  for (int i = 0; i < 10; ++i)
    data.push_back(rand() % 20);

  copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';
  cout << InvertCount(data) << '\n';
  cout << BruteForce(data) << '\n';
  return 0;
}
