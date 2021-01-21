#include <iostream>
#include <vector>

using namespace std;

template<class N, class E>
class Edge;

template<class N, class E>
class Node {
public:
  N info;
  vector<Edge<N, E> > edges;

  Node(N inf) {
    info = inf;
  }
};

template<class N, class E>
class Edge {
public:
  E value;
  Node<N, E> *destination;

  Edge(Node<N, E> *dest, E val) {
    value = val;
    destination = dest;
  }
};

template<class N, class E>
class Graph {
  vector<Node<N, E> *> nodes;
public:
  Graph();
  ~Graph();
  Graph &addNode(const N &inf);
  Graph &addEdge(const N &begin, const N &end, const E &val);
  Graph & removeEdge(const N &begin, const N &end);
  E & edgeValue(const N &begin, const N &end);
  unsigned numEdges() const;
  unsigned numNodes() const;
  size_t nodeExist(const N &inf);
  void print(std::ostream &os) const;
};

template<class N, class E>
std::ostream &operator<<(std::ostream &out, const Graph<N, E> &g);


// exception NodeAlreadyExists
template<class N>
class NodeAlreadyExists {
public:
  N info;

  NodeAlreadyExists(N inf) { info = inf; }
};

template<class N>
std::ostream &operator<<(std::ostream &out, const NodeAlreadyExists<N> &no) {
  out << "Node already exists: " << no.info;
  return out;
}


// exception NodeDoesNotExist
template<class N>
class NodeDoesNotExist {
public:
  N info;

  NodeDoesNotExist(N inf) {
    info = inf;
  }
};


template<class N>
std::ostream &operator<<(std::ostream &out, const NodeDoesNotExist<N> &no) {
  out << "Node does not exist: " << no.info;
  return out;
}

// exception EdgeAlreadyExist
template<class N>
class EdgeAlreadyExists {
public:
  N begin;
  N end;

  EdgeAlreadyExists(N b, N e) {
    begin = b;
    end = e;
  }
};

template<class N>
std::ostream &operator<<(std::ostream &out, const EdgeAlreadyExists<N> &no) {
  out << "Edge already exists: " << no.begin << " , " << no.end;
  return out;
}

// exception EdgeDoesNotExist
template<class N>
class EdgeDoesNotExist {
public:
  N begin;
  N end;

  EdgeDoesNotExist(N b, N e) {
    begin = b;
    end = e;
  }
};

template<class N>
std::ostream &operator<<(std::ostream &out, const EdgeDoesNotExist<N> &no) {
  out << "Edge does not exist: " << no.begin << " , " << no.end;
  return out;
}


template<class N, class E>
Graph<N, E>::Graph() = default;

template<class N, class E>
Graph<N, E>::~Graph() = default;

template<class N, class E>
unsigned Graph<N, E>::numNodes() const {
  // cout << "Nodes: " << nodes.size() << endl;
  return nodes.size();
}

template<class N, class E>
unsigned Graph<N, E>::numEdges() const {
  int s = 0;
  for (size_t i = 0; i < nodes.size(); i++) {
    s += nodes[i]->edges.size();
  }
  return s;
}

template<class N, class E>
Graph<N, E> &Graph<N, E>::addNode(const N &inf) {
  for (size_t i = 0; i < nodes.size(); i++) {
    if (nodes[i]->info == inf) {
      NodeAlreadyExists<N> node(inf);
      throw node;
    }
  }
  Node<N, E> *node = new Node<N, E>(inf);
  nodes.push_back(node);
  return *this;
}

template<class N, class E>
Graph<N, E> &Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
  size_t b = -1, e = -1;
  for (size_t i = 0; i < nodes.size(); i++) {
    if (nodes[i]->info == begin) {
      b = i;
    }
    if (nodes[i]->info == end) {
      e = i;
    }
  }
  if (e == -1) {
    throw NodeDoesNotExist<N>(end);
  }
  else if (b == -1) {
    throw NodeDoesNotExist<N>(begin);
  }
  else {
    for (size_t i = 0; i < (*nodes[b]).edges.size();i++){
      if (nodes[e] == nodes[b]->edges[i].destination){
        throw EdgeAlreadyExists<N>(begin, end);
      }
    }
    Edge<N,E> edge(nodes[e], val);
    nodes[b]->edges.push_back(edge);
  }
  return *this;
}

template <class N, class E>
size_t Graph<N,E>::nodeExist(const N &inf) {
  for (size_t i = 0; i < nodes.size(); i++) {
    if (nodes[i]->info == inf)
      return i;
  }
  return -1;
}

template <class N, class E>
E & Graph<N,E>::edgeValue(const N &begin, const N &end) {
  size_t nb = nodeExist(begin), ne = nodeExist(end);
  if (nb == -1)
    throw NodeDoesNotExist<N>(begin);
  else if (ne == -1)
    throw NodeDoesNotExist<N>(end);
  else {
    for (size_t i = 0; i < nodes[nb]->edges.size(); i++) {
      if (nodes[ne] == nodes[nb]->edges[i].destination) {
        return nodes[nb]->edges[i].value;
      }
    }
    throw EdgeDoesNotExist<N>(begin, end);
  }
}

template <class N, class E>
Graph<N,E> & Graph<N,E>::removeEdge(const N &begin, const N &end) {
  size_t nb = nodeExist(begin), ne = nodeExist(end);
  if (nb == -1)
    throw NodeDoesNotExist<N>(begin);
  else if (ne == -1)
    throw NodeDoesNotExist<N>(end);
  else {
    for (size_t i = 0; i < nodes[nb]->edges.size(); i++) {
      if (nodes[ne] == nodes[nb]->edges[i].destination) {
        nodes[nb]->edges.erase(nodes[nb]->edges.begin()+i);
        return *this;
      }
    }
    throw EdgeDoesNotExist<N>(begin, end);
  }
}

template<class N, class E>
void Graph<N,E>::print(std::ostream &os) const {
  for (size_t  i = 0; i < nodes.size(); i++){
    os << "( " << nodes[i]->info;
    for (size_t j = 0; j < nodes[i]->edges.size(); j++){
      os << "[ " << nodes[i]->edges[j].destination->info << " " << nodes[i]->edges[j].value << "] ";
    }
    os << ") ";
  }
}

template <class N, class E>
std::ostream &operator<<(std::ostream &out, const Graph<N,E> &graph) {
  graph.print(out);
  return out;
}