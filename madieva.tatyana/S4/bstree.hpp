#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <utility>
#include <stdexcept>
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
    Node(const Key & k, const Value & v);
    Node(Key && k, Value && v);
    ~Node() = default;
  };

  template < class Key, class Value, class Compare >
  class BSTree {
    Node< Key, Value, Compare> * root_;
    Compare cmp_;
    Node< Key, Value, Compare > * minimum(Node< Key, Value, Compare > * node);
    Node< Key, Value, Compare > * maximum(Node< Key, Value, Compare > * node);
  public:
    BSTree();
    void push(const Key & k, const Value & v);
    const Value & get(const Key & k) const;
    Value & get(const Key & k);
    void drop(const Key & k);
    ~BSTree();
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

  template < class Key, class Value, class Compare>
  Node< Key, Value, Compare > * BSTree< Key, Value, Compare >::minimum(Node< Key, Value, Compare > * node)
  {
    if (!node) {
      return nullptr;
    }
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  template < class Key, class Value, class Compare >
  Node< Key, Value, Compare > * BSTree< Key, Value, Compare >::maximum(Node< Key, Value, Compare >* node) {
    if (!node) {
      return nullptr;
    }
    while (node->right) {
      node = node->right;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::BSTree() :
    root_(nullptr),
    cmp_()
  {}

  template < class Key, class Value, class Compare>
  void BSTree< Key, Value, Compare >::push(const Key & k, const Value & v)
  {
    try {
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
    } catch (...) {
      delete n;
      throw;
    }
  }

  template < class Key, class Value, class Compare>
  const Value & BSTree< Key, Value, Compare >::get(const Key & k) const
  {
    const Node< Key, Value, Compare > * curr = root_;
    while(curr) {
      if (cmp_(k, curr->data.first)) {
        curr = curr->left;
      } else if (cmp_(curr->data.first, k)) {
        curr = curr->right;
      } else {
        return curr->data.second;
      }
    }
    throw std::out_of_range("Key not found");
  }

  template < class Key, class Value, class Compare>
  Value & BSTree< Key, Value, Compare >::get(const Key & k)
  {
    Node< Key, Value, Compare > * curr = root_;
    while(curr) {
      if (cmp_(k, curr->data.first)) {
        curr = curr->left;
      } else if (cmp_(curr->data.first, k)) {
        curr = curr->right;
      } else {
        return curr->data.second;
      }
    }
    throw std::out_of_range("Key not found");
  }

  template < class Key, class Value, class Compare>
  void BSTree< Key, Value, Compare >::drop(const Key & k)
  {
    Node< Key, Value, Compare > * curr = root_;
    while(curr) {
      if (cmp_(k, curr->data.first)) {
        curr = curr->left;
      } else if (cmp_(curr->data.first, k)) {
        curr = curr->right;
      } else {
        if (!curr->left && !curr->right) {
          if (curr->parent) {
            if (curr->parent->left == curr) {
              curr->parent->left = nullptr;
            } else {
              curr->parent->right = nullptr;
            }
          } else {
            root_ = nullptr;
          }
          delete curr;
          return;
        }
        if (!curr->left || !curr->right) {
          Node< Key, Value, Compare > * child = curr->left ? curr->left : curr->right;
          child->parent = curr->parent;
          if (curr->parent) {
            if (curr->parent->left == curr) {
              curr->parent->left = child;
            } else {
              curr->parent->right = child;
            }
          } else {
            root_ = child;
          }
          delete curr;
          return;
        }
        Node< Key, Value, Compare > * succ = minimum(curr->right);
        curr->data = std::move(succ->data);
        Node< Key, Value, Compare > * succ_child = succ->right;
        if (succ->parent != curr) {
          succ->parent->left = succ_child;
        } else {
          curr->right = succ_child;
        }
        if (succ_child) {
          succ_child->parent = succ->parent;
        }
        delete succ;
        return;
      }
    }
    throw std::out_of_range("Key not found");
  }

}

#endif
