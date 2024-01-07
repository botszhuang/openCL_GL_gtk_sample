#include "openCL_err.h"
#include "cl_buffer_struct.h"

static const size_t global_size = 1024 ; 
static const size_t local_size  = 64 ;     

static cl_kernel kernel ;

void init_dynamics_Kernel( cl_program program , 
                          cl_buffer_struct * B_field ,
                          cl_buffer_struct * momentum ) 
{ 
  cl_int err ;

  kernel = clCreateKernel( program , "dynamics_kernel", &err);

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem)        , (void *)&( B_field->cl   )); clErr ( err ) ;
  err = clSetKernelArg(kernel, 1, sizeof(cl_mem)        , (void *)&( momentum->cl  )); clErr ( err ) ;
  err = clSetKernelArg(kernel, 2, sizeof( unsigned int ), (void *)&( momentum->Num )); clErr ( err ) ;
}
void lauch_dynamics_Kernel ( cl_command_queue queue )
{
  clErr ( clEnqueueNDRangeKernel ( queue , kernel, 1, NULL,
                         &global_size, &local_size,
                         0, NULL,
                         NULL ) ) ;
}
void free_dynamics_kernel()
{
  clErr ( clReleaseKernel(kernel) ) ;
}
