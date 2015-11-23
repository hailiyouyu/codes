#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <vector>
#include <iostream>

namespace algos {
namespace ds {
class Graph {
public:
  typedef size_t vertex_type;
  struct Edge {
    vertex_type v;
    vertex_type w;
    Edge(vertex_type v, vertex_type w) : v(v), w(w) {}
  };
  typedef Edge edge_type;
  typedef size_t size_type;
  Graph(size_type vsize) :  _matrix(vsize, std::vector<bool>(vsize, false)) {}
  void InsertEdge(edge_type e) {
    assert(e.v < _matrix.size() && e.w < _matrix.size());
    if (e.v != e.w) {
      _matrix[e.v][e.w] = true;
      _matrix[e.w][e.v] = true;
    }
  }
  void RemoveEdge(edge_type e) {
    assert(e.v < _matrix.size() && e.w < _matrix.size());
    _matrix[e.v][e.w] = false;
    _matrix[e.w][e.v] = false;
  }
  std::vector<edge_type> Edges() const {
    std::vector<edge_type> res;
    for (auto i = 0; i != _matrix.size(); ++i)
      for (auto j = i + 1; j != _matrix.size(); ++j)
        if (_matrix[i][j])
          res.push_back(Edge(i, j));
    return res;
  }
  void Show() const {
    for (auto i = 0; i != _matrix.size(); ++i) {
      std::cout << i << ": ";
      for (auto j = 0; j != _matrix.size(); ++j)
        if (_matrix[i][j])
          std::cout << j << ' ';
      std::cout << '\n';
    }
  }
  size_type VSize() const {
    return _matrix.size();
  }
  bool PathExists(vertex_type v, vertex_type w) {
    std::vector<bool> visited(_matrix.size(), false);
    return PathExists(v, w, visited);
  }
private:
  std::vector<std::vector<bool>> _matrix;
  bool PathExists(vertex_type v, vertex_type w, std::vector<bool>& visited) {
    if (v == w)
      return true;
    visited[v] = true;
    for (auto i = 0; i != _matrix.size(); ++i)
      if (_matrix[v][i])
        if (!visited[i])
          if (PathExists(i, w, visited))
            return true;
    return false;
  }

};
}
}
#endif
