#include "openCL_err.h"
#include "platFormStruct.h"
#include "cl_buffer_struct.h"

#define init_cpu_mem(a,N)                 \
{                                         \
    a->Num = N;                           \
    a->bytes = a->Num * sizeof(myDouble); \
    a->data = (void *)malloc(a->bytes);   \
                                          \
}
void print_cl_buffer_struct_profile ( cl_buffer_struct * a , char * name )
{
    printf("%s:\n",name ) ;                         
    printf("\tn = %i\n", a->Num);         
    printf("\tbytes = %i\n", a->bytes);   
    print_separation_line;                
}
void print_gl_cl_buffer_struct_profile ( gl_cl_buffer_struct * a , char * name )
{
    printf("%s:\n",name ) ;                         
    printf("\tn = %i\n", a->Num);         
    printf("\tbytes = %i\n", a->bytes);   
    print_separation_line;                
}
void init_cl_buffer_struct_mem  (  cl_buffer_struct * cl , const unsigned int N , platFormStruct * p )
{
    init_cpu_mem ( cl, N ) ;

    cl_int err ;

    cl->cl = clCreateBuffer ( p->context , 
                               CL_MEM_READ_WRITE ,
                               cl->bytes ,
                               NULL, &err); 
    clErr(err);    
}
void init_gl_cl_buffer_struct_mem ( gl_cl_buffer_struct * gl  , const unsigned int N , platFormStruct * p )
{
    init_cpu_mem ( gl, N ) ;

    glGenBuffers (1, &(gl->gl) );
    glBindBuffer (GL_ARRAY_BUFFER, gl->gl );
    glBufferData (GL_ARRAY_BUFFER, gl->bytes, gl->data , GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    cl_int err ;
    gl->cl = clCreateFromGLBuffer( p->context , 
                                  CL_MEM_READ_WRITE, 
                                  gl->gl , &err);   
    clErr(err); 
}
#undef init_cpu_mem
