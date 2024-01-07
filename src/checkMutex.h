#ifndef CHECK_MUTEX_H
#define CHECK_MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define checkResults(string, val) {             \
 if (val) {                                     \
   printf("Failed with %d at %s", val, string); \
   exit(1);                                     \
 }                                              \
}

#endif