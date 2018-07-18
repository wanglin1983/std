#ifndef __MY_STD_TIMER_H_
#define __MY_STD_TIMER_H_

#include "init.h"
#include <time.h>

namespace mystd {

class timer
{
  public:
    timer():ended_(false) {
      start();
    }

    ~timer() {
      if (!ended_)
        end();
    }

    void start() {
      start_time_ = clock();
    }

    void end(const char* desc = nullptr) {
      ended_ = true;
      clock_t finish_time = clock();
      clock_t waste_time = finish_time - start_time_;
      if (desc) {
        log_info_s("[%s] Cost time : [%ld]ms", desc, waste_time);
      } else
        log_info_s("Cost time : [%ld]ms", waste_time);
      start();
    }
    
  private:
    clock_t start_time_;
    bool ended_;
};

} // namespace mystd

#endif
