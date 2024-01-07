#ifndef OPENCL_CHECK_ERROR_H
#define OPENCL_CHECK_ERROR_H

#include <stdio.h>
#include "my_CL_GL.h"

int clCheckError( int errorCode, const char * filename , const unsigned int lineNum  ) ;

#define clErr(x) clCheckError(x , __FILE__, __LINE__ )

#endif