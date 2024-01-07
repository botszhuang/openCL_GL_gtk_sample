#include "platFormStruct.h"

void init_queue ( cl_command_queue  *q , platFormStruct * p  ) 
{
  cl_int err ;  

  cl_queue_properties properties[] = {0};
  *q = clCreateCommandQueueWithProperties(p->context, p->device_list[0], properties, &err);
  clErr( err ) ;

}
void free_queue ( cl_command_queue q ) 
{
  cl_int err = clReleaseCommandQueue( q ) ;
}
