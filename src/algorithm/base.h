#ifndef __MY_STD_ALGORITHM_BASE_H__
#define __MY_STD_ALGORITHM_BASE_H__

namespace mystd {
namespace algorithm {
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
} // namespace algorithm
} // namespace mystd
#endif
