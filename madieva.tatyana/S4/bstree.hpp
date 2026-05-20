#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <utility>

namespace madieva {
  template< class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class Node {
    Node< Key, Value, Compare > * left, * right, * parent;
    std::pair< Key, Value > data;
    friend class BSTree< Key, Value, Compare >;
  public:
    Node(const Key & k,const Value & v);
    Node(Key && k, Value && v);
    ~Node() = default;
  };

  template < class Key, class Value, class Compare>
  class BSTree {
    Node< Key, Value, Compare> * root_;
    Compare cmp_;

  public:
    void push(Key k, Value v);
    const Value & get(const Key k) const;
    Value & get(const Key k);
    drop(Key k);
  };




  template < class Key, class Value, class Compare>
  Node< Key, Value, Compare >::Node(const Key & k,const Value & v) :
    data(k, v),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}

  template < class Key, class Value, class Compare>
  Node< Key, Value, Compare >::Node(Key && k, Value && v) : 
    data(std::move(k), std::move(v)),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}

}





#endif
