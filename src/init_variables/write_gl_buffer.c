#include <math.h>
#include <stdio.h>

#include "cl_buffer_struct.h"
#include "platFormStruct.h"

void write_gl_buffer ( cl_command_queue queue ,
                       gl_cl_buffer_struct gl )
{
    static cl_int   err ;
    static cl_event acEvent ;
    static cl_event writeEvent ;

    err = clEnqueueAcquireGLObjects ( queue , 1 , & ( gl.cl ) , 
                                    0 , NULL , 
                                    & acEvent ); 
                                    clErr ( err ) ; 

    err = clEnqueueWriteBuffer( queue , gl.cl, CL_TRUE,
                           0, gl.bytes, gl.data,
                           1, & acEvent ,
                           & writeEvent  ) ;
                       
    err = clReleaseEvent ( acEvent ) ; clErr ( err ) ; 

    err = clEnqueueReleaseGLObjects ( queue , 1 , & ( gl.cl ) ,
                                    1 ,  & writeEvent ,
                                    NULL ) ;
                                    clErr ( err ) ;

    err = clReleaseEvent ( writeEvent ) ; clErr ( err ) ; 
}

