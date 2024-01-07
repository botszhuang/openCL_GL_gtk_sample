#include "checkMutex.h"
#include "variable_collection_struct.h"
#include <unistd.h>

#include <gtk/gtk.h> 
#include "gtkRUN.h"

#include "my_cl_function.h"
#include "init_variable.h"
#include "objects.h"


global_variable_Struct global_variable ; 

void init_global_variable_main(){
  global_variable.openCLRUN = false ;
  global_variable.B_amp.x = 5 ;
  global_variable.B_amp.y = 0 ;
  global_variable.B_amp.z = 0 ; 
}
global_variable_Struct * get_global_variable_pointer () 
{
  return ( & global_variable ) ;
}

static const unsigned int X_Num = 1000000 ;

static platFormStruct platform ;
static cl_command_queue queue ;

static cl_buffer_struct grid ;
static cl_buffer_struct momentum ;
static cl_buffer_struct B_field ;

static gl_cl_buffer_struct gl_grid ;
static gl_cl_buffer_struct gl_momentum ;

static pthread_mutex_t cl_write_mutex = PTHREAD_MUTEX_INITIALIZER ;
static pthread_mutex_t cl_read_mutex = PTHREAD_MUTEX_INITIALIZER ;
static cl_int err ;

#define WriteCLBuffer( queue , clBuffer ){\
    err = pthread_mutex_lock(  & cl_write_mutex  );  checkResults("pthread_mutex_lock()\n", err );\
    err = clEnqueueWriteBuffer( queue , clBuffer.cl, CL_TRUE, 0, clBuffer.bytes, clBuffer.data, 0, NULL, NULL ) ; clErr (err) ; \
    err = pthread_mutex_unlock( & cl_write_mutex );  checkResults("pthread_mutex_unlock()\n", err );\
    }
static void init_kernels () 
{ 
  init_dynamics_Kernel( platform.program , &B_field , &momentum ) ; 
}
void draw_openCL_data ( GLfloat tMatrxi [16] ){
  draw_objects( tMatrxi  , gl_grid , gl_momentum ) ;
}
void init_openCL () {
  
  puts ("init openCL ......") ;  

  init_platForm ( & platform ) ;
  init_cl_buffer_struct_mem ( & grid     ,  X_Num , & platform ) ;
  init_cl_buffer_struct_mem ( & momentum ,  X_Num , & platform ) ;

  gl_grid     = make_gl_copy ( grid     , platform ) ;
  gl_momentum = make_gl_copy ( momentum , platform ) ; 
}
void free_openCL ()
{
  puts ("free openCL ......") ;  

  err = clFlush(queue);
  err = clFinish(queue);

    free_cl_buffer_struct ( & grid ) ; 
    free_cl_buffer_struct ( & momentum ) ;
    free_gl_cl_buffer_struct ( & gl_grid ) ;
    free_gl_cl_buffer_struct ( & gl_momentum ) ;

  free_dynamics_kernel();
  free_program  ( & platform );
  free_queue    ( queue ) ;
  free_platForm ( platform ) ;

  err = pthread_mutex_destroy( & cl_write_mutex );  
  checkResults("pthread_mutex_destroy()\n", err );

}
void * openCLmain() {
 
  puts ("running openCLmain......") ;   

  print_cl_buffer_struct_profile  ( & grid     , "grid" ) ;
  set_grid_data_at_cup_mem     ( & grid ) ;

  print_cl_buffer_struct_profile  ( & momentum , "momentum" ) ;
  set_momentum_data_at_cup_mem ( & momentum ) ;

  init_cl_buffer_struct_mem ( & B_field , 1 , & platform ) ;
  print_cl_buffer_struct_profile  ( & B_field  , "B field" ) ;
  free ( B_field.data ) ;
  B_field.data = ( void * ) ( & ( global_variable.B_amp )) ;

  init_program  ( & platform ) ;
  init_kernels ( ) ;
  init_queue ( & queue , & platform ) ;
  puts ("\t...queue ...") ;

  WriteCLBuffer ( queue , grid     ) ;
  WriteCLBuffer ( queue , momentum ) ;
  WriteCLBuffer ( queue , B_field  ) ;

  puts ("\t...WriteCLBuffer ...") ;

  unsigned int i = 0 ;
  while ( global_variable.openCLRUN )
  { 
    i++ ; 
    WriteCLBuffer ( queue , B_field  ) ;
    lauch_dynamics_Kernel ( queue ) ;

    if ( ( i % 10 ) == 9 ) 
    { 
      i = 0 ;

      err = pthread_mutex_lock(  & cl_write_mutex  );
      checkResults("pthread_mutex_lock()\n", err );
      clErr ( clEnqueueReadBuffer( queue , grid.cl     , CL_TRUE, 0, grid.bytes     ,  grid.data     , 0, NULL, NULL) );
      err = pthread_mutex_unlock( & cl_write_mutex );
      checkResults("pthread_mutex_unlock()\n", err );

      err = pthread_mutex_lock(  & cl_write_mutex  );
      checkResults("pthread_mutex_lock()\n", err );
      clErr ( clEnqueueReadBuffer( queue , momentum.cl , CL_TRUE, 0, momentum.bytes ,  momentum.data , 0, NULL, NULL) ); 
      err = pthread_mutex_unlock( & cl_write_mutex );
      checkResults("pthread_mutex_unlock()\n", err );
 
      puts ("\tsleeping 0.01 second... ") ;
      usleep( 10000 ); 
    }
  }
  pthread_exit(NULL);
}
#undef WriteCLBuffer
