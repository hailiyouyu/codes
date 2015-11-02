#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<int>::iterator Iter;
typedef vector<int>::value_type value_type;

value_type Median(Iter begin, Iter end) {
  auto size = end - begin;
  if (size & 0x1)
    return *(begin + size/2);
  else
    return (*(begin + size/2) + *(begin+size/2-1)) / 2;
}

value_type GetMedian(Iter beginA, Iter endA, Iter beginB, Iter endB) {
  if (beginA + 1 == endA)
    return (*beginA + *beginB) / 2;
  if (beginA + 2 == endA)
    return (max(*beginA, *beginB) + min(*(beginA+1), *(beginB+1))) / 2;
  auto medianA = Median(beginA, endA);
  auto medianB = Median(beginB, endB);
  auto size = endA - beginA;
  if (medianA == medianB)
    return medianA;
  else if (medianA < medianB) {
    if (size & 0x1)
      return GetMedian(beginA + size/2, endA, beginB, beginB + size - size/2);
    else
      return GetMedian(beginA + size/2 - 1, endA, beginB, beginB + size/2 + 1);
  } else {
    if (size & 0x1)
      return GetMedian(beginA, beginA + size - size/2, beginB + size/2, endB);
    else
      return GetMedian(beginA, beginA + size/2 + 1, beginB + size/2 - 1, endB);
  }
}

double GetMedian2(vector<int>& A, vector<int>& B) {
  int m = A.size();
  int n = B.size();
  if (m > n)
    return GetMedian2(B, A);
  int l = 0, r = m, half_len = (m + n + 1) / 2;
  int i, j, num1, num2;
  while (l <= r) {
    i = l + (r - l) / 2;
    j = half_len - i;
    if (i < m && j > 0 && B[j-1] > A[i])
      l = i + 1;
    else if (i > 0 && j < n && A[i-1] > B[j])
      r = i - 1;
    else {
      if (i == 0)
        num1 = B[j-1];
      else if (j == 0)
        num1 = A[i-1];
      else
        num1 = max(A[i-1], B[j-1]);
      if ((m + n) & 0x1)
        return num1;
      if (i == m)
        num2 = B[j];
      else if (j == n)
        num2 = A[i];
      else
        num2 = min(A[i], B[j]);
      return (num1 + num2) / 2.0;
    }
  }
}

int main() {
  srand(time(0));
  vector<int> a, b;
  for (int i = 0; i < 10; ++i) {
    a.push_back(rand() % 20);
    b.push_back(rand() % 20);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';
  copy(b.begin(), b.end(), ostream_iterator<int>(cout, " "));
  cout << '\n';

  //cout << GetMedian(a.begin(), a.end(), b.begin(), b.end()) << '\n';

  {
    vector<int> A = {-100, -1, 0, 50, 60, 100};
    vector<int> B = {9, 10, 30, 40, 50, 60};
    cout << GetMedian(A.begin(), A.end(),  B.begin(), B.end()) << '\n';
  }
  {
    vector<int> A = {-1, 0, 50, 60};
    vector<int> B = {9, 10, 30, 40, 50, 60};
    cout << GetMedian2(A, B) << '\n';
  }
  {
    vector<int> A = {1, 2, 3, 4};
    vector<int> B = {9, 10, 11, 12, 13};
    cout << GetMedian2(A, B) << '\n';
  }
  {
    vector<int> A = {7, 8, 9, 10};
    vector<int> B = {9, 10, 11, 12, 13, 14};
    cout << GetMedian2(A, B) << '\n';
  }
  {
    vector<int> A = {9, 10, 11, 12};
    vector<int> B = {1, 2, 3, 4, 5};
    cout << GetMedian2(A, B) << '\n';
  }
  {
    vector<int> A = {9, 10, 11, 12};
    vector<int> B = {1, 2, 3, 4, 5, 6};
    cout << GetMedian2(A, B) << '\n';
  }
  {
    vector<int> A = {1, 6, 9, 12};
    vector<int> B = {4, 7, 8, 10, 13};
    cout << GetMedian2(A, B) << '\n';
  }


  return 0;
}
