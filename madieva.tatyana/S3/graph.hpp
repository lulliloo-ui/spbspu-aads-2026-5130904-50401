#ifndef GRAPH_HPP
#define GRAPH_HPP
#define XXH_INLINE_ALL

#include <string>
#include "hash_table.hpp"
#include "../common/xxhash.h"

namespace madieva {
   struct PairHash {
    size_t operator()(const std::pair< std::string, std::string > & k) const;
  };

  struct PairEqual {
    bool operator()(const std::pair< std::string, std::string > & a,
      const std::pair< std::string, std::string > & b) const;
  };

  class Graph {
    std::string name_graph;
    using key = std::pair<std::string, std::string>;
    using val = List< size_t >;
    HashTable< key, val, PairHash, PairEqual > edge_;
    List< std::string > vertex_;
  public:
    Graph(const std::string & name);
    const std::string & getName() const;
    void addVertex(const std::string & v);
    bool hasVertex(const std::string & v) const;
    const List< std::string > & getVertices() const;
    HashTable< key, val, PairHash, PairEqual > & getEdges();
    const HashTable< key, val, PairHash, PairEqual > & getEdges() const;
    void addEdge(const std::string & a, const std::string & b, size_t e);
    void addEdge(const key & a, size_t weight);

  };

  size_t PairHash::operator()(const std::pair< std::string, std::string > & k) const
  {
    XXH64_hash_t h = XXH64(k.first.data(), k.first.size(), 0);
    h = XXH64(k.second.data(), k.second.size(), h);
    return static_cast< size_t >(h);
  }

  bool PairEqual::operator()(const std::pair< std::string, std::string > & a,
    const std::pair< std::string, std::string > & b) const
  {
    return a.first == b.first && a.second == b.second;
  }

  Graph::Graph(const std::string & name) :
    name_graph(name)
  {}

  const std::string & Graph::getName() const
  {
    return name_graph;
  }

  void Graph::addVertex(const std::string & v)
  {
    if (!hasVertex(v)) {
      vertex_.push_back(v);
    }
  }

  bool Graph::hasVertex(const std::string & v) const
  {
    LCIter< std::string > it = vertex_.begin();
    for (size_t i = 0; i < vertex_.size(); ++i) {
      if ((*it) == v) {
        return true;
      }
      ++it;
    }
    return false;
  }

  const List< std::string > & Graph::getVertices() const
  {
    return vertex_;
  }

  HashTable< Graph::key, Graph::val, PairHash, PairEqual > & Graph::getEdges()
  {
    return edge_;
  }

  const HashTable< Graph::key, Graph::val, PairHash, PairEqual > & Graph::getEdges() const
  {
    return edge_;
  }

  void Graph::addEdge(const std::string & a, const std::string & b, size_t weight)
  {
    key k = {a, b};
    addEdge(k, weight);
    addVertex(a);
    addVertex(b);
  }

  void Graph::addEdge(const key & a, size_t weight)
  {
    if (edge_.has(a)) {
      edge_.get(a).push_back(weight);
    } else {
      List< size_t > list;
      list.push_back(weight);
      edge_.add(a, list);
    }
  }


}

#endif
