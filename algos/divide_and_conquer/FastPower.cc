// Fast Power
// Time Complexity: O(lgn)

#include <iostream>
using namespace std;

int Power(int x, unsigned int y) {
  if (y == 0)
    return 1;
  int t = Power(x, y/2);
  if (y & 0x1)
    return t * t * x;
  else
    return t * t;
}

int main() {
  cout << Power(4, 5) << '\n';
  cout << Power(-2, 7) << '\n';
  return 0;
}
