#ifndef PLATFORM_STRUCT_H
#define PLATFORM_STRUCT_H

#include "mytype.h"

typedef struct 
{
    cl_platform_id *platforms ;
    cl_uint platformNum ;
    cl_device_id *device_list ;
    cl_uint deviceNum;
    cl_context context;
    cl_program program;
} platFormStruct ;

#endif