#ifndef OBJECTS_H
#define OBJECTS_H

#include "my_CL_GL.h"
#include "cl_buffer_struct.h"

void init_objects ( );
void free_objects ();
/*void draw_objects ( GLfloat tMatrxi [16] , 
                    GLuint vbo[] , 
                    const unsigned int arrayNum );
                    */
void draw_objects ( GLfloat tMatrxi [16] , 
                    gl_cl_buffer_struct grid ,
                    gl_cl_buffer_struct momentum );
#endif
