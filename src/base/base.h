#ifndef __MY_STD_BASE_H__
#define __MY_STD_BASE_H__

#include <cstdlib>
#include <ctime>
#include <iostream>

typedef long long LL;
typedef unsigned int UINT;

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

  template<typename T>
  void swap(T& t1, T& t2) {
    const T temp = t1;
    t1 = t2;
    t2 = temp;
  }

  template<typename T>
  void swap(T t[], int i, int j) {
    const T temp = t[i];
    t[i] = t[j];
    t[j] = temp;
  }

  template<typename T>
  T max(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
  }

  template<typename T>
  T min(T t1, T t2) {
    return t1 < t2 ? t1 : t2;
  }
} // namespace mystd

#endif
