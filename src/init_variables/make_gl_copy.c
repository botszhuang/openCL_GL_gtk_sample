#include <math.h>
#include <stdio.h>

#include "cl_buffer_struct.h"
#include "platFormStruct.h"

gl_cl_buffer_struct make_gl_copy ( const cl_buffer_struct cl , 
                                  const platFormStruct p )
{
    gl_cl_buffer_struct gl;

    gl.Num  = cl.Num  ;
    gl.data = cl.data ;

    gl.bytes = gl.Num * sizeof(myDouble);  

    glGenBuffers (1, &(gl.gl) );
    glBindBuffer (GL_ARRAY_BUFFER, gl.gl );
    glBufferData (GL_ARRAY_BUFFER, gl.bytes, gl.data , GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    cl_int err ;
    gl.cl = clCreateFromGLBuffer( p.context , 
                                  CL_MEM_READ_WRITE, 
                                  gl.gl , &err);   
                                  clErr(err);
    return gl ;    
}

