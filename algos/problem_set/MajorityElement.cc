#include <iostream>
#include <vector>

using namespace std;

// O(n)
bool CheckForce(vector<int>& data, int x) {
  int count = 0;
  for (int i = 0; i != data.size(); ++i)
    if (data[i] == x)
      ++count;
  return count >= (data.size()+1)/2;
}

int BinarySearch(vector<int>& data, int x);

// O(lgn)
bool IsMajority(vector<int>& data, int x) {
  int i = BinarySearch(data, x);
  if (i == -1)
    return false;
  int u = i + (data.size()+1)/2 - 1;
  return u < data.size() && data[u] == x;
}

// search the first occurrence of x
int BinarySearch(vector<int>& data, int x) {
  int l, m, h;
  l = 0;
  h = data.size() - 1;
  while (l <= h) {
    m = l + (h-l) / 2;
    if (data[m] == x && (m == 0 || data[m-1] < x))
      return m;
    else if (data[m] < x)
      l = m+1;
    else
      h = m-1;
  }
  return -1;
}


int main() {
  cout << boolalpha;
  {
    vector<int> data = {1, 2, 3, 3, 3, 3, 10};
    cout << CheckForce(data, 3) << '\n';
    cout << IsMajority(data, 3) << '\n';
  }
  {
    vector<int> data = {1, 1, 2, 4, 4, 4, 6, 6};
    cout << CheckForce(data, 4) << '\n';
    cout << IsMajority(data, 4) << '\n';
  }
  {
    vector<int> data = {1, 1, 1, 2, 2};
    cout << CheckForce(data, 1) << '\n';
    cout << IsMajority(data, 1) << '\n';
  }
  return 0;
}
