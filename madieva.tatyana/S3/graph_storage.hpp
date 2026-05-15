#ifndef GRAPH_STORAGE_HPP
#define GRAPH_STORAGE_HPP

#include <string>
#include "hash_table.hpp"
#include "graph.hpp"
#include "../common/xxhash.h"

namespace madieva {
  struct StringHash {
    size_t operator()(const std::string & a) const;
  };
  struct StringEqual {
    bool operator()(const std::string & lhs, const std::string & rhs) const;
  };
  class GraphStorage {
    HashTable< std::string, Graph, StringHash, StringEqual > graphs_;
  public:
    GraphStorage() = default;
    GraphStorage();
    void addGraph(const std::string & name, const Graph & graph);
    bool hasGraph(const std::string & name);
    Graph & getGraph(const std::string & name);
    const Graph & getGraph(const std::string & name) const;
    void removeGraph(const std::string & name);
  };
}


#endif
