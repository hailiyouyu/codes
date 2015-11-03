// Multiplication: multiply two n-digit number
// 1. divide two n-digit numbers into 4 n/2 numbers
// 2. using identity: (10**m a + b)*(10**m c + d) = 10**2m ac + 10**m (bc+ad) + bd
// 3. (a-b)*(c-d) = ac+bd-(bc+ad)  ==========> bc+ad = ac+bc-(a-b)(c-d)
// 4.decrease 4 times multiply to 3 times

// Time Complexity:
// T(n) <= 3T(n/2) + O(n) == > T(n) = O(n**lg3) ~ O(n**1.585)

int FastMultiply(int x, int y, int n) {
  if (n == 1)
    return x * y;
  int m = ceil(n/2.0);
  int p = pow(10, m);
  int a = x / p;
  int b = x % p;
  int c = y / p;
  int d = y % p;
  int e = FastMultiply(a, c, m);
  int f = FastMultiply(b, d, m);
  int g = FastMultiply(a-b, c-d);
  return pow(10, 2*m)*e + pow(10, m)(e+f-g)+f;
}
