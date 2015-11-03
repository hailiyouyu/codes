// Hanoi Tower
// move n dishes from A to C use B
// 1. move n-1 dishes from A to B use C
// 2. move the nth dish from A to C directly
// 3. move n-1 dishes from B to C use A


// Correctness proof: using Induction
//
// 1. n = 0, then nothing to do
// 2. induction hypothesis: Assume that hanoi_tower algorithm works for k dishes, then
//   for k+1 dishes, first move k dishes from A to B use C; then move the (k+1)th dish from A to C; finally, move k dishes in B to C with A.
// 3. therfore, hanoi_tower works fine for n k+1 dishes

// T(0) = 0;
// T(n) = 2*T(n-1) + 1, n >= 1

// T(n) = O(2^n);


#include <iostream>
using namespace std;
void hanoi_tower(int n, char a, char b, char c) {
  if (n > 0) {
    hanoi_tower(n-1, a, c, b);
    cout << "move " << n << " from " << a << " to " << c << '\n';
    hanoi_tower(n-1, b, c, a);
  }
}

int main() {
  int n;
  cin >> n;
  cout << "Steps to move " << n << " dishes from A to C use B:" << '\n';
  hanoi_tower(n, 'A', 'B', 'C');
  return 0;
}
