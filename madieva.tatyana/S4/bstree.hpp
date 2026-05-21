#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <utility>
#include <cstddef>

namespace madieva {
  template< class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class Node {
    Node< Key, Value, Compare > * left;
    Node< Key, Value, Compare > * right;
    Node< Key, Value, Compare > * parent;
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
    BSTree();
    void push(Key k, Value v);
    const Value & get(const Key k) const;
    Value & get(const Key k);
    void drop(Key k);
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

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::BSTree() :
    root_(nullptr),
    cmp_()
  {}

  template < class Key, class Value, class Compare>
  void BSTree< Key, Value, Compare >::push(Key k, Value v)
  {
    Node< Key, Value, Compare > * n = new Node< Key, Value, Compare >(k, v);
    if (!root_) {
      root_ = n;
      return;
    }
    Node< Key, Value, Compare > * curr = root_;
    while (curr) {
      if (cmp_(n->data.first, curr->data.first)) {
        if (!curr->left) {
          curr->left = n;
          n->parent = curr;
          return;
        }
        curr = curr->left;
      } else if (cmp_(curr->data.first, n->data.first)) {
        if (!curr->right) {
          curr->right = n;
          n->parent = curr;
          return;
        }
        curr = curr->right;
      } else {
        delete n;
        return;
      }
    }
  }

  template < class Key, class Value, class Compare>
  const Value & BSTree< Key, Value, Compare >::get(const Key k) const
  {

  }


}





#endif
