#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include "../common/vector.hpp"
#include "../common/list.hpp"
#include <stdexcept>
namespace madieva {

  template< class Key, class Value, class Hash, class Equal >
  class HashTable {
    using Pair = std::pair<Key, Value>;
    Vector< List< Pair > > buckets_;
    Hash hasher_;
    Equal comparer_;
    size_t count_;
    size_t getIndex(const Key& k) const;
  public:
    explicit HashTable(size_t count = 16);
    void add(Key k, Value v);
    bool has(Key k);
    Value & get(Key k);
    Value drop(Key k);
    void rehash(size_t slots);
    size_t size() const noexcept;
    bool empty() const noexcept;
  };

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::getIndex(const Key& k) const {
    return hasher_(k) % buckets_.getSize();
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(size_t count) :
    buckets_()
  {
    buckets_.reserve(count);
    for(size_t i = 0; i < count; ++i) {
      buckets_.pushBack(List< Pair >());
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::add(Key k, Value v)
  {
    size_t index = getIndex(k);
    List< Pair > & bucket = buckets_[index];
    LIter< Pair > it = bucket.begin();
    for (size_t i = 0; i < bucket.size(); ++i) {
      if (comparer_((*it).first, k)) {
        (*it).second = v;
        return;
      }
      ++it;
    }
    bucket.push_back(std::make_pair(k, v));
    ++count_;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::has(Key k)
  {
    size_t index = getIndex(k);
    List< Pair > & bucket = buckets_[index];
    LIter< Pair > it = bucket.begin();
    for (size_t i = 0; i < bucket.size(); ++i) {
      if (comparer_((*it).first, k)) {
        return true;
      }
      ++it;
    }
    return false;
  }

  template< class Key, class Value, class Hash, class Equal >
  Value & HashTable< Key, Value, Hash, Equal >::get(Key k)
  {
    size_t index = getIndex(k);
    List< Pair > & bucket = buckets_[index];
    LIter< Pair > it = bucket.begin();
    for (size_t i = 0; i < bucket.size(); ++i) {
      if (comparer_((*it).first, k)) {
        return (*it).secound;
      }
      ++it;
    }
    throw std::out_of_range("no such key\n");
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::size() const noexcept
  {
    return count_;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::empty() const noexcept
  {
    return count_ == 0;
  }
}

#endif
