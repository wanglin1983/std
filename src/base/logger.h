#ifndef __MY_STD_LOGGER_H_
#define __MY_STD_LOGGER_H_

#include <stdio.h>
#include <iomanip>
#include <sstream>

#define DEBUG_MODE 1

namespace mystd {
#ifdef _WIN32
#define log_debug(logs, ...) fprintf(stderr, "[%s] [%s:%d]: " logs "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#define log_info_s(logs, ...) fprintf(stderr, logs "\n", ##__VA_ARGS__);
#else
#define log_error(logs, ...) fprintf(stderr, "\033[01;31;40m[%s] [%s:%d]: " logs "\033[0m\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#define log_debug(logs, ...) fprintf(stderr, "\033[01;32;40m[%s:%d]: " logs "\033[0m\n", __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#define log_info(logs, ...) fprintf(stderr, "\033[01;34;40m[%s] [%s:%d]: " logs "\033[0m\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#define log_info_s(logs, ...) fprintf(stderr, "\033[01;34;40m" logs "\033[0m\n", ##__VA_ARGS__);
#endif
  class LOG {
  public:
    enum LogType {
      INFO,
      DEBUG,
      ERROR
    };

    LOG(LogType type) {
      type_ = type;
    }

  private:
    LogType type_;
  };
}

#endif
