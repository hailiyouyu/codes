#include <iostream>
#include <vector>
using namespace std;

bool SubsetSum(int *data, int n, int sum) {
  if (sum == 0)
    return true;
  if (sum < 0 || n == 0)
    return false;
  return SubsetSum(data, n-1, sum) || SubsetSum(data, n-1, sum-data[n-1]);
}


int main() {
  cout << boolalpha;
  {
    int data[] = {8, 6, 7, 5, 3, 10, 9};
    cout << SubsetSum(data, 7, 0) << '\n';
    cout << SubsetSum(data, 7, 15) << '\n';
  }
  {
    int data[] = {4, 8, 7, 2, 9};
    cout << SubsetSum(data, 5, 5) << '\n';
  }
  return 0;
}
