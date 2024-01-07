#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "cl_buffer_struct.h"

void init_dynamics_Kernel( cl_program program , 
                          cl_buffer_struct * grid ,
                          cl_buffer_struct * velocity ) ;
void lauch_dynamics_Kernel ( cl_command_queue queue );
void free_dynamics_kernel();

#endif