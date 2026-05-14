#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
#include "hash_table.hpp"

namespace madieva {
   struct PairHash {
    size_t operator()(const std::pair< std::string, std::string > & k) const
    {
      XXH64_hash_t h = XXH64(k.first.data(), k.first.size(), 0);
      h = XXH64(k.second.data(), k.second.size(), h);
      return static_cast<size_t>(h);
    }
  };

  struct PairEqual {
    bool operator()(const std::pair< std::string, std::string > & a,
      const std::pair< std::string, std::string > & b) const
    {
      return a.first == b.first && a.second == b.second;
    }
  };
  class Graph {
    std::string name_graph;
    using key = std::pair<std::string, std::string>;
    using val = List< size_t >;
    HashTable< key, val, , > edge_;
    List< std::string > vertex_;
  public:
    Graph(std::string & name);
  };

  Graph::Graph(std::string & name) :
    name_graph(name)
  {}
}

#endif