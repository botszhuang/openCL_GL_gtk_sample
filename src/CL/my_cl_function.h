#ifndef MY_CL_FUNCTION_H
#define MY_CL_FUNCTION_H

#include "platFormStruct.h"
#include "dynamics.h"

void init_platForm ( platFormStruct * p ) ;
void free_platForm ( platFormStruct   p ) ;

void init_program ( platFormStruct * p );
void free_program ( platFormStruct * p );

void init_queue ( cl_command_queue  *q , platFormStruct * p  ) ;
void free_queue ( cl_command_queue q ) ;


#endif
