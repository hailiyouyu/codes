#include "graph.h"
#include <iostream>
using namespace std;
using namespace algos::ds;

int main() {
  Graph g(7);
  g.InsertEdge(Graph::Edge(0, 1));
  g.InsertEdge(Graph::Edge(0, 2));
  g.InsertEdge(Graph::Edge(0, 5));
  g.InsertEdge(Graph::Edge(0, 6));
  g.InsertEdge(Graph::Edge(1, 2));
  g.InsertEdge(Graph::Edge(2, 3));
  g.InsertEdge(Graph::Edge(2, 4));
  g.InsertEdge(Graph::Edge(3, 4));
  g.InsertEdge(Graph::Edge(4, 5));
  g.InsertEdge(Graph::Edge(4, 6));

  cout << boolalpha;
  cout << g.PathExists(2, 6) << '\n';
  cout << g.PathExists(3, 6) << '\n';
}


