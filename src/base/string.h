#ifndef __MYSTD_STRING_H__
#define __MYSTD_STRING_H_

namespace mystd {
  void StrCopy(char* dest, char* src) {
    if (!dest || !src)
      return;

    while (*src)
      *dest++ = *src++;
    *dest = '\0';
  }

  bool StrSame(char* str1, char* str2) {
    if (!str1 || !str2)
      return false;
    while (*str1 && *str2 && *str1 == *str2) {
      ++str1;
      ++str2;
    }
    return (!*str1 && !*str2);
  }
}

#endif __MYSTD_STRING_H__