#include <string.h>
#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>
#include <epoxy/gl.h>
#include "miniTool.h"
#include "vsfsProgram.h"

static const GLfloat vertex_data[] = {
  0.f,   0.5f,   0.f, 1.f,
  0.5f, -0.366f, 0.f, 1.f,
 -0.5f, -0.366f, 0.f, 1.f,
};

static GLuint program   ;

static GLuint vao, buffer;
static GLint tMatrixLocation ;

static void init_buffers ()
{
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);

  glGenBuffers (1, &buffer);
  glBindBuffer (GL_ARRAY_BUFFER, buffer);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertex_data), vertex_data, GL_STATIC_DRAW);
  glBindBuffer (GL_ARRAY_BUFFER, 0);

}

void init_triangleProgram ()
{
  program = init_vsfsProgram( "src/GL/VSFS/triangle/vs.glsl" ,  "src/GL/VSFS/triangle/fs.glsl" ) ;

  init_buffers () ;
  tMatrixLocation = glGetUniformLocation( program , "tMatrix");
}
void free_triangleProgram (void)
{
 glDeleteBuffers (1, &buffer);
 glDeleteVertexArrays ( 1 , & vao );
 glDeleteProgram ( program ) ;
}
void draw_triangleProgram ( GLfloat tMatrxi [16] )
{
  glUseProgram ( program);

  glBindBuffer (GL_ARRAY_BUFFER, buffer);
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, 0);

 	glUniformMatrix4fv( tMatrixLocation , 1, GL_FALSE, tMatrxi );

  glDrawArrays (GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glUseProgram (0);
}

