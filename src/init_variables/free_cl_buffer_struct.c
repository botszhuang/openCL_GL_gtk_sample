#include "openCL_err.h"
#include "checkMutex.h"

#include "cl_buffer_struct.h"

void free_cl_buffer_struct ( cl_buffer_struct * a )
{
   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;
   int err = pthread_mutex_lock(  & mutex  );  
   checkResults("pthread_mutex_lock()\n", err );

   if ( ( a->cl   ) != NULL ){ clErr ( clReleaseMemObject (  a->cl  ) ) ; }
   if ( ( a->data ) != NULL ){ free (  a->data  ) ;  }
   
   err = pthread_mutex_unlock( & mutex );  
   checkResults("pthread_mutex_unlock()\n", err );
   
   err = pthread_mutex_destroy( & mutex );  
   checkResults("pthread_mutex_destroy()\n", err );

}
void free_gl_cl_buffer_struct ( gl_cl_buffer_struct * a )
{
   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;
   int err = pthread_mutex_lock(  & mutex  );  
   checkResults("pthread_mutex_lock()\n", err );

   if ( ( a->cl   ) != NULL ){ clErr ( clReleaseMemObject (  a->cl  ) ) ; }
   if ( ( a->gl   ) != 0    ){ glDeleteBuffers ( 1 , & ( a->gl ) ) ;  }
   
   err = pthread_mutex_unlock( & mutex );  
   checkResults("pthread_mutex_unlock()\n", err );
   
   err = pthread_mutex_destroy( & mutex );  
   checkResults("pthread_mutex_destroy()\n", err );
}
