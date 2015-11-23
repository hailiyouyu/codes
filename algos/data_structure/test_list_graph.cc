#include "list_graph.h"
#include <iostream>
using namespace std;
using namespace algos::ds;
int main() {
  ListGraph g(13);
  g.InsertEdge(ListGraph::Edge(0, 1));
  g.InsertEdge(ListGraph::Edge(0, 2));
  g.InsertEdge(ListGraph::Edge(0, 5));
  g.InsertEdge(ListGraph::Edge(0, 6));
  g.InsertEdge(ListGraph::Edge(3, 4));
  g.InsertEdge(ListGraph::Edge(3, 5));
  g.InsertEdge(ListGraph::Edge(4, 5));
  g.InsertEdge(ListGraph::Edge(4, 6));
  g.InsertEdge(ListGraph::Edge(7, 8));
  g.InsertEdge(ListGraph::Edge(9, 10));
  g.InsertEdge(ListGraph::Edge(9, 11));
  g.InsertEdge(ListGraph::Edge(9, 12));
  g.InsertEdge(ListGraph::Edge(11, 12));
  g.Show();
  return 0;
}
