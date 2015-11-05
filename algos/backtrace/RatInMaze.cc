#include <iostream>
#include <vector>
using namespace std;

const vector<int> next_row = {0, 1};
const vector<int> next_col = {1, 0};
void FindPath(vector<vector<int>>& maze, vector<vector<int>>& res, int is, int js, int id, int jd) {
  if (is == id && js == jd) {
    for (const auto& row : res) {
      for (auto col : row)
        cout << col << ' ';
      cout << '\n';
    }
    cout << "-------------\n";
  } else {
    for (int r = 0; r < next_row.size(); ++r) {
      int new_i = is + next_row[r];
      int new_j = js + next_col[r];
      bool back = false;
      if (new_i < maze.size() && new_i >= 0 && new_j < maze.size() && new_j >= 0 && maze[new_i][new_j] != 0) {
        res[new_i][new_j] = 1;
        FindPath(maze, res, new_i, new_j, id, jd);
        back = true;
      }
      if (back) {
        res[new_i][new_j] = 0;
      }
    }
  }
}

int main() {
  {
    vector<vector<int>> maze = {{1, 0, 0, 0}, {1, 1, 0, 1}, {0, 1, 0, 0}, {1, 1, 1, 1}};
    vector<vector<int>> res(maze.size(), vector<int>(maze[0].size(), 0));
    res[0][0] = 1;
    FindPath(maze, res, 0, 0, maze.size()-1, maze[0].size()-1);
  }
  return 0;
}
