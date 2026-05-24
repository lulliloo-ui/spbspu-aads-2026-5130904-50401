#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cassert>

namespace madieva {
  template< class T > class List;
  template< class T > class LIter;
  template< class T > class LCIter;

  namespace detail {
    template< class T >
    struct node_t {
      T val;
      node_t< T > * next;
      node_t< T > * prev;
    };
  }
  template< class T >
  class LIter {
  public:
    LIter<T> & operator++() noexcept;
    LIter<T> & operator--() noexcept;
    LIter<T> operator++(int) noexcept;
    LIter<T> operator--(int) noexcept;
    bool operator==(const LIter< T > & a) const noexcept;
    bool operator!=(const LIter< T > & a) const noexcept;
    T & operator*() noexcept;
    T * operator->() noexcept;
  private:
    friend class List< T >;
    detail::node_t< T > * it;
    LIter(detail::node_t< T > * a) noexcept;
  };

  template< class T >
  class LCIter {
  public:
    LCIter<T> & operator++() noexcept;
    LCIter<T> & operator--() noexcept;
    LCIter<T> operator++(int) noexcept;
    LCIter<T> operator--(int) noexcept;
    bool operator==(const LCIter< T > & a) const noexcept;
    bool operator!=(const LCIter< T > & a) const noexcept;
    const T & operator*() const noexcept;
    const T * operator->() const noexcept;
  private:
    friend class List< T >;
    const detail::node_t< T > * it;
    LCIter(const detail::node_t< T > * a) noexcept;
  };

  template< class T >
  class List {
  public:
    List() noexcept;
    List(const List& a);
    ~List() noexcept;
    List& operator=(const List& a);
    void clear() noexcept;
    void push_front(const T & a);
    void push_front(const T && a);
    void push_back(const T & a);
    void push_back(const T && a);
    void pop_front() noexcept;
    void pop_back() noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    LIter< T > begin() noexcept;
    LCIter< T > begin() const noexcept;
    LCIter< T > cbegin() const noexcept;
    LIter< T > end() noexcept;
    LCIter< T > end() const noexcept;
    LCIter< T > cend() const noexcept;
  private:
    detail::node_t< T > * head;
    size_t size_;
  };

  template< class T >
  LIter< T >::LIter(detail::node_t< T > * a) noexcept :
    it(a)
  {}

  template< class T >
  LIter<T> & LIter< T >::operator++() noexcept
  {
    assert(it);
    it = it->next;
    return *this;
  }

  template< class T >
  LIter<T> & LIter< T >::operator--() noexcept
  {
    assert(it);
    it = it->prev;
    return *this;
  }

  template< class T >
  LIter<T> LIter< T >::operator++(int) noexcept
  {
    assert(it);
    LIter<T> temp = *this;
    it = it->next;
    return temp;
  }

  template< class T >
  LIter<T> LIter< T >::operator--(int) noexcept
  {
    assert(it);
    LIter<T> temp = *this;
    it = it->prev;
    return temp;
  }

  template< class T >
  bool LIter< T >::operator==(const LIter< T > & a) const noexcept
  {
    return(it == a.it);
  }

  template< class T >
  bool LIter< T >::operator!=(const LIter< T > & a) const noexcept
  {
    return(it != a.it);
  }

  template< class T >
  T & LIter< T >::operator*() noexcept
  {
    assert(it);
    return it->val;
  }

  template< class T >
  T * LIter< T >::operator->() noexcept
  {
    assert(it);
    return &(it->val);
  }

  template< class T >
  LCIter< T >::LCIter(const detail::node_t< T > * a) noexcept :
    it(a)
  {}

  template< class T >
  LCIter<T> & LCIter< T >::operator++() noexcept
  {
    assert(it);
    it = it->next;
    return *this;
  }

  template< class T >
  LCIter<T> & LCIter< T >::operator--() noexcept
  {
    assert(it);
    it = it->prev;
    return *this;
  }

  template< class T >
  LCIter<T> LCIter< T >::operator++(int) noexcept
  {
    assert(it);
    LCIter<T> temp = *this;
    it = it->next;
    return temp;
  }

  template< class T >
  LCIter<T> LCIter< T >::operator--(int) noexcept
  {
    assert(it);
    LCIter<T> temp = *this;
    it = it->next;
    return temp;
  }

  template< class T >
  bool LCIter< T >::operator==(const LCIter< T > & a) const noexcept
  {
    return(it == a.it);
  }

  template< class T >
  bool LCIter< T >::operator!=(const LCIter< T > & a) const noexcept
  {
    return(it != a.it);
  }

  template< class T >
  const T & LCIter< T >::operator*() const noexcept
  {
    assert(it);
    return it->val;
  }

  template< class T >
  const T * LCIter< T >::operator->() const noexcept
  {
    assert(it);
    return &(it->val);
  }

  template< class T >
  List< T >::List() noexcept :
    head(nullptr),
    size_(0)
  {}

  template< class T >
  List< T >::~List() noexcept
  {
    clear();
  }

  template< class T >
  List< T >::List(const List< T > & a) :
    head(nullptr),
    size_(0)
  {
    detail::node_t< T > * temp = a.head;
    for (size_t i = 0; i < a.size_; ++i) {
      this->push_back(temp->val);
      temp = temp->next;
    }
  }

  template< class T >
  List< T > & List< T >::operator=(const List< T > & a)
  {
    if(this == &a) {
      return *(this);
    }
    this->clear();
    detail::node_t< T > * temp = a.head;
    for (size_t i = 0; i < a.size_; ++i) {
      this->push_back(temp->val);
      temp = temp->next;
    }
    return *(this);
  }

  template< class T >
  void List< T >::clear() noexcept
  {
    if (head) {
      detail::node_t< T > * end = head->prev;
      while (head != end) {
        detail::node_t< T > * temp = head->next;
        delete head;
        head = temp;
      }
      delete head;
      head = nullptr;
      size_ = 0;
    }
  }

  template< class T >
  LIter< T > List< T >::begin() noexcept
  {
    return LIter< T >(head);
  }

  template< class T >
  LCIter< T > List< T >::begin() const noexcept
  {
    return LCIter< T >(head);
  }

  template< class T >
  LCIter< T > List< T >::cbegin() const noexcept
  {
    return LCIter< T >(head);
  }

  template< class T >
  LIter< T > List< T >::end() noexcept
  {
    return LIter< T >(head);
  }

  template< class T >
  LCIter< T > List< T >::end() const noexcept
  {
    return LCIter< T >(head);
  }

  template< class T >
  LCIter< T > List< T >::cend() const noexcept
  {
    return LCIter< T >(head);
  }

  template< class T >
  void List< T >::push_front(const T & a)
  {
    if (!head) {
      head = new detail::node_t< T >{a, nullptr, nullptr};
      head->next = head;
      head->prev = head;
      size_ = 1;
    } else {
      detail::node_t< T > * temp = new detail::node_t< T >{a, head, head->prev};
      head->prev->next = temp;
      head->prev = temp;
      head = temp;
      size_++;
    }
  }

  template< class T >
  void List< T >::push_front(const T && a)
  {
    if (!head) {
      head = new detail::node_t< T >{std::move(a), nullptr, nullptr};
      head->next = head;
      head->prev = head;
      size_ = 1;
    } else {
      detail::node_t< T > * temp = new detail::node_t< T >{std::move(a), head, head->prev};
      head->prev->next = temp;
      head->prev = temp;
      head = temp;
      size_++;
    }
  }

  template< class T >
  void List< T >::push_back(const T & a)
  {
    if (!head) {
      head = new detail::node_t< T >{a, nullptr, nullptr};
      head->next = head;
      head->prev = head;
      size_ = 1;
    } else {
      detail::node_t< T > * temp = new detail::node_t< T >{a, head, head->prev};
      head->prev->next = temp;
      head->prev = temp;
      size_++;
    }
  }

  template< class T >
  void List< T >::push_back(const T && a)
  {
    if (!head) {
      head = new detail::node_t< T >{std::move(a), nullptr, nullptr};
      head->next = head;
      head->prev = head;
      size_ = 1;
    } else {
      detail::node_t< T > * temp = new detail::node_t< T >{std::move(a), head, head->prev};
      head->prev->next = temp;
      head->prev = temp;
      size_++;
    }
  }

  template< class T >
  void List< T >::pop_front() noexcept
  {
    if(size_) {
      if(size_ == 1) {
        delete head;
        head = nullptr;
        size_ = 0;
      } else {
        head->next->prev = head->prev;
        head->prev->next = head->next;
        detail::node_t< T > * a = head->next;
        delete head;
        head = a;
        size_--;
      }
    }
  }

  template< class T >
  void List< T >::pop_back() noexcept
  {
    if (size_) {
      if(size_ == 1) {
        delete head;
        head= nullptr;
        size_ = 0;
      } else{
        detail::node_t< T > * a = head->prev;
        a->next->prev = a->prev;
        a->prev->next = a->next;
        delete a;
        size_--;
      }
    }
  }

  template< class T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }

  template< class T >
  bool List< T >::empty() const noexcept
  {
    return !size_;
  }

}

#endif
