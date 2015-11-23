#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include <vector>
#include <cassert>
#include <iostream>

namespace algos {
namespace ds {
  class ListGraph {
  public:
    typedef size_t vertex_type;
    typedef size_t size_type;
    struct Edge {
      vertex_type _v;
      vertex_type _w;
      Edge(vertex_type v, vertex_type w) : _v(v), _w(w) {}
    };
    struct Link {
      vertex_type _v;
      Link* _next;
      Link(vertex_type v = 0) : _v(v), _next(nullptr) {}
      Link(vertex_type v, Link* l) : _v(v), _next(l) {}
    };
    typedef Edge edge_type;
    ListGraph(size_type vsize) : _nodes(std::vector<Link>(vsize)) {
      for (auto i = 0; i != _nodes.size(); ++i)
        _nodes[i]._v = i;
    }
    void InsertEdge(edge_type e) {
      assert(e._v < _nodes.size() && e._w < _nodes.size());
      if (e._v != e._w) {
        Link* p = _nodes[e._v]._next;
        while (p) {
          if (p->_v == e._w)
            return;
          p = p->_next;
        }
        Link* head = _nodes[e._v]._next;
        Link* newhead = new Link(e._w, nullptr);
        newhead->_next = head;
        _nodes[e._v]._next = newhead;

        head = _nodes[e._w]._next;
        newhead = new Link(e._v, nullptr);
        newhead->_next = head;
        _nodes[e._w]._next = newhead;
      }
    }
    void RemoveEdge(edge_type e) {
      assert(e._v < _nodes.size() && e._w < _nodes.size());
      remove(&_nodes[e._v], e._w);
      remove(&_nodes[e._w], e._v);
    }
    std::vector<edge_type> Edges() const {
      std::vector<edge_type> res;
      for (auto i = 0; i != _nodes.size(); ++i) {
        vertex_type v = _nodes[i]._v;
        Link* l = _nodes[i]._next;
        while (l) {
          if (v < l->_v)
            res.push_back(Edge(v, l->_v));
          l = l->_next;
        }
      }
      return res;
    }
    void Show() const {
      for (auto i = 0; i != _nodes.size(); ++i) {
        vertex_type v = _nodes[i]._v;
        Link* l = _nodes[i]._next;
        std::cout << v << ": ";
        while (l) {
          std::cout << l->_v << ' ';
          l = l->_next;
        }
        std::cout << '\n';
      }
    }
  private:
    std::vector<Link> _nodes;
    void remove(Link* pre, vertex_type v) {
      Link* p = pre->_next;
      while (p) {
        if (p->_v == v)
          break;
        pre = p;
        p = p->_next;
      }
      if (p) {
        pre->_next = pre->_next->_next;
        delete p;
      }
    }
  };
}
}
#endif
