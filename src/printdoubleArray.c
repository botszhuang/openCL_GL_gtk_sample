#include <stdio.h>

#include "mytype.h"

#define PRINT_SUBROUTINE()  {\
    for (unsigned int i = 0; i < N; i++) \
        {                                    \
            printf("%2i) % .3lf % .3lf % .3lf % .3lf\n", i , A[i].x , A[i].y, A[i].z , A[i].w ) ; \
        }                                    \
        print_separation_line;               \
    }
void printGLfloatArray(void *a, const unsigned int N)
{
   myFloat *A = a;
    PRINT_SUBROUTINE();
}
void printdoubleArray(void *a, const unsigned int N)
{
   myFloat *A = a;
    PRINT_SUBROUTINE();
}
#undef PRINT_SUBROUTINE