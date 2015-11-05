#include <iostream>
#include <vector>
using namespace std;

bool Check(vector<vector<int>>& graph, vector<int>& res, int cur, int m) {
  if (cur == graph.size())
    return true;
  for (int c = 1; c <= m; ++c) {
    bool legal = true;
    for (int i = 0; i != graph.size(); ++i)
      if (i != cur && graph[cur][i] == 1 && res[i] == c)
        legal = false;
    if (legal) {
      res[cur] = c;
      if (Check(graph, res, cur+1, m))
        return true;
    }
  }
  return false;
}

int main() {
  {
    vector<vector<int>> graph = {{0,1,1,1},{1,0,1,0},{1,1,0,1},{1,0,1,0}};
    vector<int> res(graph.size(), 0);
    int m = 2;
    if (Check(graph, res, 0, m)) {
      for (auto e : res)
        cout << e << ' ';
      cout << '\n';
    } else {
      cout << "cannot coloring this graph within " << m << " colors\n";
    }
  }
  return 0;
}
