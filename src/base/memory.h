#ifndef __MYSTD_MEMORY_H__
#define __MYSTD_MEMORY_H__

#include "base/base.h"

namespace mystd {
  void MemSet(char* array, LL size) {
    if (!array)
      return;
    for (int i = 0; i < size; ++i)
      array[i] = '\0';
  }
}

#endif