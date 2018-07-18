#ifndef __MY_STD_LIST_H_
#define __MY_STD_LIST_H_

#include "base/init.h"

namespace mystd {
namespace container {

const uint64 kMaxListSize = 10000000;

#if DEBUG_MODE
uint64 con_count = 0;
uint64 itr_count = 0;
#endif

template<typename Item>
class list
{
  public:
    typedef Item value_type;
    typedef uint64 size_type;

    class iterator;

    // container is used to reduce Item value copy when enumlating
    struct container
    {
      container() {
        prev_ = nullptr;
        next_ = nullptr;
#if DEBUG_MODE
        ++con_count;
#endif
      }

      container(const value_type& item) {
        prev_ = nullptr;
        next_ = nullptr;
        item_ = item;
#if DEBUG_MODE
        ++con_count;
#endif
      }

      ~container() {
        prev_ = nullptr;
        next_ = nullptr;
#if DEBUG_MODE
        --con_count;
#endif
      }

      value_type item_;
      iterator* itr_;
      container* prev_;
      container* next_;
    };

    // iterator for enum
    class iterator
    {
      public:
        iterator() {
          container_ = smart_ptr<container>(new container());
          container_->itr_ = this;
#if DEBUG_MODE
          ++itr_count;
#endif
        }

        iterator(const value_type& item) {
          container_ = smart_ptr<container>(new container(item));
          container_->itr_ = this;
#if DEBUG_MODE
          ++itr_count;
#endif
        }

        iterator(const iterator& other_itr) {
          container_ = other_itr.container_;
#if DEBUG_MODE
          ++itr_count;
#endif
        }

        ~iterator() {
#if DEBUG_MODE
          --itr_count;
          log_debug("%p,%lld", this, itr_count);
#endif
        }

        iterator& operator=(const iterator& other_itr) {
          container_ = other_itr.container_;
          return *this;
        }

        // compare operations
        bool operator!=(const iterator& other_itr) {
          return container_ != other_itr.container_;
        }

        bool operator==(const iterator& other_itr) {
          return container_ == other_itr.container_;
        }

        // enum operations
        iterator& operator++() {
          assert(container_->next_);
          container_ = container_->next_->itr_->container_;
          return *this;
        }

        const iterator& operator++(int) {
          iterator temp = *this;
          ++(*this);
          return temp;
        }

        bool empty() {
          return !container_.ptr();
        }

        value_type& operator*() {
          return container_->item_;
        }

        // current itr might be a value copy, return actual itr in container 
        iterator* self() {
          return container_->itr_;
        }

        iterator* next() {
          if (!container_->next_)
            return nullptr;
          else
            return container_->next_->itr_;
        }

        iterator* prev() {
          if (!container_->prev_)
            return nullptr;
          else
            return container_->prev_->itr_;
        }

        void set_next(iterator* itr) {
          container_->next_ = itr->container_.ptr();
        }

        void set_prev(iterator* itr) {
          container_->prev_ = itr->container_.ptr();
        }

        smart_ptr<container> container_;
    };

    list() {
      size_ = 0;

      begin_.set_next(&end_);
      end_.set_prev(&begin_);
    }

    ~list() {
      iterator* itr = begin_.next();
      while (!itr->empty() && itr->next()) {
        iterator* next_itr = itr->next();
#if DEBUG_MODE
        log_debug("deleting %p", itr->self());
#endif
        delete itr->self();
        itr = next_itr;
      }
    }

    // iterators
    iterator& begin() {
      return *begin_.container_->next_->itr_;
    }

    iterator& end() {
      return *end_.container_->itr_;
    }

    // capacity
    bool empty() {
      return begin_.container_->next_->itr_ == &end_;
    }

    size_type size() {
      return size_;
    }

    size_type max_size() {
      return kMaxListSize;
    }

    // element access
    value_type& front() {
      return *begin();
    }

    value_type& back() {
      return *(*end_.container_->prev_->itr_);
    }

    // list operations
    void push_back(const value_type& value) {
      iterator itr = end_;
      insert(end_, value);
    }

    void push_front(const value_type& value) {
      insert(*begin_.next(), value);
    }

    void insert(iterator itr, const value_type& value) {
      if (size_ >= kMaxListSize)
        return;

      iterator* itr_new = new iterator(value);

      // set normal iterator
      iterator* itr_prev = itr.prev();
      itr_prev->set_next(itr_new);
      itr_new->set_next(itr.self());
      itr.self()->set_prev(itr_new);
      itr_new->set_prev(itr_prev);

      ++size_;
    }

    void insert(iterator itr, size_type size, const value_type& value) {
      for (size_type i = 0; i < size; ++i)
        insert(itr, value);
    }

  private:
    iterator begin_;
    iterator end_;
    size_type size_;
};

} // namespace container
} // namespace mystd

#endif
