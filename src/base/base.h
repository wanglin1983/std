#ifndef __MY_STD_BASE_H__
#define __MY_STD_BASE_H__

#include <cstdlib>
#include <ctime>
#include <iostream>

typedef long long LL;

#ifndef NULL
#define NULL 0
#endif

namespace mystd {
  // Print array
  template<typename T>
  void print_array(T* array, int size) {
    for (int i = 0; i < size; ++i)
      std::cout << array[i] << " ";
    std::cout << std::endl;
  }

  // Random number
  void make_seed() {
    srand((unsigned)time(NULL));
  }

  LL random() {
    return rand() << 15 | rand();
  }
} // namespace mystd

#endif
