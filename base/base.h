#ifndef __MY_STD_BASE_H__
#define __MY_STD_BASE_H__

#include <iostream>

namespace mystd {
  // Print array
  template<typename T>
  void print_array(T* array, int size) {
    for (int i = 0; i < size; ++i)
      std::cout << array[i] << " ";
    std::cout << std::endl;
  }
} // namespace mystd

#endif
