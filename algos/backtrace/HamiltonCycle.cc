#include <iostream>
#include <vector>
using namespace std;

namespace {
  bool Check(vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, int cur_node, int cur_total) {
    if (cur_total == graph.size() && graph[cur_node][0] == 1) {
      path.push_back(0);
      return true;
    }
    for (int i = 0; i != graph.size(); ++i)
      if (graph[cur_node][i] != 0 && !visited[i]) {
        path.push_back(i);
        visited[i] = true;
        if (Check(graph, visited, path, i, cur_total+1)) {
          return true;
        } else {
          path.pop_back();
          visited[i] = false;
        }
      }
    return false;
  }
}

int main() {
  {
    vector<vector<int>> graph = {{0,1,0,1,0},{1,0,1,1,1},{0,1,0,0,1},{1,1,0,0,1},{0,1,1,1,0}};
    vector<bool> visited(graph.size(), false);
    visited[0] = true;
    vector<int> path;
    path.push_back(0);
    if (Check(graph, visited, path, 0, 1)) {
      for (auto& e: path)
        cout << e << ' ';
      cout << '\n';
    } else {
      cout << "This graph has not Hamilton Cycle\n";
    }
  }
  {
    vector<vector<int>> graph = {{0,1,0,1,0},{1,0,1,1,1},{0,1,0,0,1},{1,1,0,0,0},{0,1,1,0,0}};
    vector<bool> visited(graph.size(), false);
    visited[0] = true;
    vector<int> path;
    path.push_back(0);
    if (Check(graph, visited, path, 0, 0)) {
      for (auto& e: path)
        cout << e << ' ';
      cout << '\n';
    } else {
      cout << "This graph has not Hamilton Cycle\n";
    }
  }
}
