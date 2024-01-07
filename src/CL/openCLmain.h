#ifndef OPENCLMAIN_H
#define OPENCLMAIN_H

#include "cl_buffer_struct.h"
#include "variable_collection_struct.h"

void init_global_variable_main();
global_variable_Struct * get_global_variable_pointer () ;

void init_openCL  () ;
void * openCLmain ();
void free_openCL  () ;
void draw_openCL_data ( GLfloat tMatrxi [16] ) ;

#endif