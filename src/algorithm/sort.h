#ifndef __MY_STD_SORT_H__
#define __MY_STD_SORT_H__

#include <iostream>

#include "base/base.h"
#include "base/logger.h"
#include "algorithm/base.h"

namespace mystd {
namespace algorithm {

  // Insert sort
  template<typename T>
  void insert_sort(T* array, int size) {
#if DEBUG_MODE
    log_debug("size : %d", size);
#endif
    for (int i = 1; i < size; ++i) {
      const auto key = array[i];
      int j = i - 1;
      for (; j >= 0; --j) {
        const auto& value = array[j];
        if (value > key)
          array[j + 1] = value;
        else
          break;
      }
      if (j != i - 1) // if |j == i - 1|, key is at its original position
        array[j + 1] = key;
#if DEBUG_MODE
      print_array(array, size);
#endif
    }
  }

  // Bubble sort
  template<typename T>
  void bubble_sort(T* array, int size) {
#if DEBUG_MODE
    log_debug("size : %d", size);
#endif
    for (int i = 0; i < size; ++i) {
      for (int j = i + 1; j < size; ++j) {
        if (array[j] < array[i]) { // Swap min one to front
          swap(array[i], array[j]);
        }
      }
#if DEBUG_MODE
      print_array(array, size);
#endif
    }
  }

  // Quick sort
  template<typename T>
  void quick_sort_(T* array, int left, int right) {
    if (left >= right)
      return;

    T key = array[left];
    int l = left, r = right;
    while (l < r) {
      // Move smaller to left
      while (l < r && array[r] >= key)
        --r;
      array[l] = array[r];
      // Move larger to right
      while (l < r && array[l] <= key)
        ++l;
      array[r] = array[l];
    }
    array[l] = key;
    quick_sort_(array, left, l - 1);
    quick_sort_(array, l + 1, right);
  }

  template<typename T>
  void quick_sort(T* array, int size) {
    quick_sort_(array, 0, size - 1);
  }

} // namespace algorithm
} // namespace mystd

#endif
