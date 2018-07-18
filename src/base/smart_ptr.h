#ifndef __MY_STD_SMART_PTR_H_
#define __MY_STD_SMART_PTR_H_

#include <assert.h>
#include "type.h"

namespace mystd {

template<typename T>
class smart_ptr
{
  public:
    smart_ptr() {
      t_ptr_ = nullptr;
      ref_count_ = nullptr;
    }

    smart_ptr(T* t) {
      t_ptr_ = t;
      init_ref_count();
      add_ref();
    }

    smart_ptr(const smart_ptr& other) {
      if (other.t_ptr_) {
        assert(other.ref_count_);
        t_ptr_ = other.t_ptr_;
        ref_count_ = other.ref_count_;
        add_ref();
      }
    }

    ~smart_ptr() {
      reduce_ref();
    }

    smart_ptr& operator=(const smart_ptr& other) { 
      if (t_ptr_) {
        if (t_ptr_ != other.t_ptr_)
          reduce_ref();
        else
          return *this;
      }

      if (other.t_ptr_) {
        assert(other.ref_count_);
        t_ptr_ = other.t_ptr_;
        ref_count_ = other.ref_count_;
        add_ref();
      }

      return *this;
    }

    T* operator=(int) {
      return t_ptr_;
    }

    void init_ref_count() {
      ref_count_ = new int;
      *ref_count_ = 0;
    }

    T* operator->() {
      return t_ptr_;
    }

    bool operator!() {
      return t_ptr_ == nullptr;
    }

    T* ptr() {
      return t_ptr_;
    }

    bool operator==(const smart_ptr& other) {
      return t_ptr_ == other.t_ptr_; 
    }

    bool operator!=(const smart_ptr& other) {
      return t_ptr_ != other.t_ptr_; 
    }

    void add_ref() {
      ++(*ref_count_);
#if DEBUG_MODE
      log_info("ptr:%p,count_ptr:%p,count:%d", t_ptr_, ref_count_, *ref_count_);
#endif
    }

    void reduce_ref() {
      if (!ref_count_ || *ref_count_ <= 0)
        return;
#if DEBUG_MODE
      log_info("ptr:%p,count_ptr:%p,count:%d", t_ptr_, ref_count_, *ref_count_ - 1);
#endif
      if (--(*ref_count_) == 0) {
        delete ref_count_;
        ref_count_ = nullptr;
        delete t_ptr_;
        t_ptr_ = nullptr;
      }
    }

  private:
    int* ref_count_;
    T* t_ptr_;
};

template<typename T>
class auto_clean_ptr
{
  public:
    auto_clean_ptr(T* t) {
      ptr_ = t;
    }

    ~auto_clean_ptr() {
      if (ptr_) {
        delete ptr_;
        ptr_ = nullptr;
      }
    }

  private:
    T* ptr_;
};

} // namespace mystd

#endif
