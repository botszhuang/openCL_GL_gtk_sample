#ifndef MY_TYPE_H
#define MY_TYPE_H

#include "my_CL_GL.h"

#define myDouble cl_float4
#define myFloat cl_float4
#define M_PI 3.14159265358979323846

#define print_separation_line puts("-------------------------------------------------")

void printGLfloatArray(void *a, const unsigned int N);
void printdoubleArray(void *a, const unsigned int N);

#define a4_sub_b4(c, a, b) \
  {                        \
    c.x = a.x - b.x;       \
    c.y = a.y - b.y;       \
    c.z = a.z - b.z;       \
    c.w = a.w - b.w;       \
  }
#endif