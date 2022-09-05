#ifndef TIME_HELPER_H
#define TIME_HELPER_H
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

long long timeval_diff(struct timespec* tv1, struct timespec* tv2);
void delay(int number_of_seconds);

#endif /* TIME_HELPERS_H */