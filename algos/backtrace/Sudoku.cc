#include <iostream>
#include <vector>
using namespace std;

namespace {
  bool FindUnFilled(vector<vector<int>>& grid, int& r, int& c) {
    for (int i = 0; i != grid.size(); ++i)
      for (int j = 0; j != grid[0].size(); ++j)
        if (grid[i][j] == 0) {
          r = i;
          c = j;
          return true;
        }
    return false;
  }
  bool ValidRow(vector<vector<int>>& grid, int row, int n) {
    for (int i = 0; i < grid[0].size(); ++i)
      if (grid[row][i] == n)
        return false;
    return true;
  }
  bool ValidColumn(vector<vector<int>>& grid, int col, int n) {
    for (int i = 0; i < grid.size(); ++i)
      if (grid[i][col] == n)
        return false;
    return true;
  }
  bool ValidGrid(vector<vector<int>>& grid, int row, int col, int n) {
    int r = row / 3, c = col / 3;
    for (int i = r * 3; i < r * 3 + 3; ++i)
      for (int j = c * 3; j < c * 3 + 3; ++j)
        if (grid[i][j] == n)
          return false;
    return true;
  }
  bool Check(vector<vector<int>>& grid) {
    int row, col;
    if (!FindUnFilled(grid, row, col))
      return true;
    for (int i = 1; i <= 9; ++i) {
      if (ValidRow(grid, row, i) && ValidColumn(grid, col, i) && ValidGrid(grid, row, col, i)) {
        grid[row][col] = i;
        if (Check(grid))
          return true;
        else {
          grid[row][col] = 0;
        }
      }
    }
    return false;
  }
}

int main() {
  {
    vector<vector<int>> grid = {{3,0,6,5,0,8,4,0,0},
                                {5,2,0,0,0,0,0,0,0},
                                {0,8,7,0,0,0,0,3,1},
                                {0,0,3,0,1,0,0,8,0},
                                {9,0,0,8,6,3,0,0,5},
                                {0,5,0,0,9,0,6,0,0},
                                {1,3,0,0,0,0,2,5,0},
                                {0,0,0,0,0,0,0,7,4},
                                {0,0,5,2,0,6,3,0,0}};
    if (Check(grid)) {
      for (auto& row: grid) {
        for (auto e : row)
          cout << e << ' ';
        cout << '\n';
      }
    } else {
      cout << "No solution exists\n";
    }
  }
  return 0;
}
