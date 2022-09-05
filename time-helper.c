#include "time-helper.h"

long long timeval_diff(struct timespec* tv1, struct timespec* tv2) {
  long long diff = 0;
  // calculate the diffrence of the nanoseconds
  long nano = (tv2->tv_nsec - tv1->tv_nsec);
  int add = 0;

  // some calculations if the nanoseconds of struct 1 were bigger
  if(nano < 0) {
    nano = 1000000000 + nano;
    add = 1;
  }
  diff = nano;
  // add the seconds
  diff += (tv2->tv_sec - tv1->tv_sec - add) * 1000000000;
  return diff;
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
