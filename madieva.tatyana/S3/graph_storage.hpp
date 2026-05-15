#ifndef GRAPH_STORAGE_HPP
#define GRAPH_STORAGE_HPP

#include <string>
#include <stdexcept>
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
    void addGraph(const std::string & name, const Graph & graph);
    bool hasGraph(const std::string & name) const;
    Graph & getGraph(const std::string & name);
    const Graph & getGraph(const std::string & name) const;
    List<std::string> getAllNames() const;
    void removeGraph(const std::string & name);
    size_t size() const;
    bool empty() const;
  };

  size_t StringHash::operator()(const std::string & a) const
  {
    XXH64_hash_t h = XXH64(a.data(), a.size(), 0);
    return static_cast< size_t >(h);
  }

  bool StringEqual::operator()(const std::string & lhs, const std::string & rhs) const
  {
    return lhs == rhs;
  }

  void GraphStorage::addGraph(const std::string & name, const Graph & graph)
  {
    if (graphs_.has(name)) {
      throw std::runtime_error("Graph already exists");
    } else {
      graphs_.add(name, graph);
    }
  }

  bool GraphStorage::hasGraph(const std::string& name) const
  {
    return graphs_.has(name);
  }

  Graph& GraphStorage::getGraph(const std::string& name) {
    return graphs_.get(name);
  }

  const Graph& GraphStorage::getGraph(const std::string& name) const {
    return graphs_.get(name);
  }

  List<std::string> GraphStorage::getAllNames() const {
    List<std::string> names;
    HTCIter< std::string, Graph, StringHash, StringEqual > it = graphs_.begin();
    for (size_t i = 0; i < graphs_.size(); ++i) {
      names.push_back((*it).first);
      ++it;
    }
    return names;
  }

  void GraphStorage::removeGraph(const std::string& name) {
    graphs_.drop(name);
  }

  size_t GraphStorage::size() const
  {
    return graphs_.size();
  }
  bool GraphStorage::empty() const
  {
    return graphs_.empty();
  }

}


#endif
