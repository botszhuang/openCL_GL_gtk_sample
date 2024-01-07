#ifndef CL_BUFFER_STRUCT_H
#define CL_BUFFER_STRUCT_H

#include "platFormStruct.h"

typedef  struct { 
    cl_mem cl ;
    unsigned int bytes ; 
    unsigned int Num ;
    void * data ;
    } cl_buffer_struct ;

typedef  struct {
    GLuint gl ; 
    cl_mem cl ;
    unsigned int bytes ; 
    unsigned int Num ;
    void * data ;
    } gl_cl_buffer_struct ;

void print_cl_buffer_struct_profile    ( cl_buffer_struct    * a , char * name ) ;
void print_gl_cl_buffer_struct_profile ( gl_cl_buffer_struct * a , char * name ) ;

void init_cl_buffer_struct_mem    (    cl_buffer_struct * cl , const unsigned int N , platFormStruct * p ) ;
void init_gl_cl_buffer_struct_mem ( gl_cl_buffer_struct * gl , const unsigned int N , platFormStruct * p ) ;

void free_cl_buffer_struct    (    cl_buffer_struct * a ) ;
void free_gl_cl_buffer_struct ( gl_cl_buffer_struct * a ) ;

gl_cl_buffer_struct make_gl_copy ( const cl_buffer_struct cl , const platFormStruct p ) ;
void copy_cl_to_gl_buffer ( cl_command_queue queue ,
                                gl_cl_buffer_struct gl , 
                            const cl_buffer_struct cl  ) ;
void write_gl_buffer ( cl_command_queue queue ,
                       gl_cl_buffer_struct gl ) ;                            

#endif