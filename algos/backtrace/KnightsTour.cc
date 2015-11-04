#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int N = 8;
bool board[N][N] = {false};
int row[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int col[] = {-1, 1, -2, 2, -2, 2, -1, 1};
// board is the chess board, n is the line and column
// i is the previous line number, j is the previous column number
// k is the current step
// first step is board[0][0]

typedef pair<int, int> point_t;

void KnightTour(vector<point_t>& res, int i, int j, int k) {
  if (k == N * N) {
    for (auto& point : res)
      cout << '(' << point.first << ", " << point.second << ") ";
    cout << '\n';
    return;
  }
  for (int r = 0; r < 8; ++r) {
    int next_i = i + row[r];
    int next_j = j + col[r];
    bool legal = false;
    if (next_i >= 0 && next_i < N && next_j >= 0 && next_j < N && board[next_i][next_j] == false) {
      legal = true;
      board[next_i][next_j] = true;
      res.push_back(make_pair(next_i, next_j));
      KnightTour(res, next_i, next_j, k+1);
    }
    if (legal) {
      board[next_i][next_j] = false;
      res.pop_back();
    }
  }
}

void KnightTour() {
  vector<point_t> res;
  board[0][0] = true;
  KnightTour(res, 0, 0, 1);
}

int main() {
  KnightTour();
  return 0;
}
