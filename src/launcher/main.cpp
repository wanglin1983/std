#include "algorithm/sort.h"
#include "base/base.h"
#include "base/timer.h"

using namespace mystd;

#define MAX_ARR 100000000

enum TestType
{
	// Sort
	SORT_INSERT,
	SORT_BUBBLE,
	SORT_QUICK,
	SORT_HEAP
};

LL arr_int[MAX_ARR];

void init() {
  make_seed();
  for (int i = 0; i < MAX_ARR; ++i)
    arr_int[i] = random() % MAX_ARR;
}

TestType test_type = SORT_QUICK;

int main() {
  init();
  switch (test_type)
  {
  case SORT_INSERT:
  {
    timer tm;
    algorithm::insert_sort(arr_int, MAX_ARR);
    tm.end("insert sort");
    printf("%d\n", arr_int[MAX_ARR - 1]);
    break;
  }
  case SORT_BUBBLE:
    algorithm::bubble_sort(arr_int, MAX_ARR);
    printf("%d\n", arr_int[MAX_ARR - 1]);
    break;
  case SORT_QUICK:
  {
    timer tm;
    // print_array(arr_int, MAX_ARR);
    algorithm::quick_sort(arr_int, MAX_ARR);
    tm.end("quick sort");
    printf("%d\n", arr_int[MAX_ARR - 1]);
    // print_array(arr_int, MAX_ARR);
    break;
  }
  case SORT_HEAP:
  {
    timer tm;
    // print_array(arr_int, MAX_ARR);
    algorithm::heap_sort(arr_int, MAX_ARR);
    tm.end("heap sort");
    printf("%d\n", arr_int[MAX_ARR - 1]);
    // print_array(arr_int, MAX_ARR);
    break;
  }
  default:
    break;
  }
	return 0;
}