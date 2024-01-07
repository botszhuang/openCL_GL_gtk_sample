#include <math.h>
#include <stdio.h>

#include "cl_buffer_struct.h"
#include "platFormStruct.h"

cl_event finish_copy_data ;

void copy_cl_to_gl_buffer ( cl_command_queue queue ,
                                gl_cl_buffer_struct gl , 
                            const cl_buffer_struct cl  )
{
    static cl_int   err ;
    static cl_event acEvent ;
    static cl_event copyEvent ;

    err = clEnqueueAcquireGLObjects ( queue , 1 , & ( gl.cl ) , 
                                    0 , NULL , 
                                    & acEvent ); 
                                    clErr ( err ) ; 

    err = clEnqueueCopyBuffer(   queue,
                           cl.cl , gl.cl , 0 , 0 , cl.bytes ,
                           1, & acEvent ,
                           & copyEvent ) ; clErr ( err ) ;

    err = clReleaseEvent ( acEvent ) ; clErr ( err ) ; 

    err = clEnqueueReleaseGLObjects ( queue , 1 , & ( gl.cl ) ,
                                    1 ,  & copyEvent ,
                                    & finish_copy_data ) ;
                                    clErr ( err ) ;

    err = clReleaseEvent ( copyEvent ) ; clErr ( err ) ; 

}

