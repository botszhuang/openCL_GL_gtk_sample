#include "vsfsProgram.h"
#include "const_extern_parameter.h"

static GLint x = 5 ;
static GLint y = 5 ;
static GLint width  = 10 ;
static GLint height = 10 ;

static GLuint vbo [1] = { 0 } ;
static GLuint vao = 0 ;
static GLuint program ;
static GLint tMatrixLocation ;

static const float points[] = {
   0,  0,  0,
   1,  0,  0,
   0,  0,  0,
   0,  1,  0,
   0,  0,  0,
   0,  0,  1,
};
static void init_buffers(){

    glGenBuffers( 1, vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  
}

void init_coordinateMarker()
{ 
    program = init_vsfsProgram( "src/GL/VSFS/coordinateMarker/vs.glsl" , "src/GL/VSFS/coordinateMarker/fs.glsl" ) ;
    init_buffers () ;
    tMatrixLocation = glGetUniformLocation( program , "tMatrix");

    width  = (int) ( windowSizeX /5.0 )  ;
    height = (int) ( windowSizeY /5.0 )  ;
    printf ( "axis: %d, %d , %d, %d\n", x, y, width, height ) ;


}
void free_coordinateMarker()
{
    glDeleteBuffers      ( 1 ,   vbo );
    glDeleteVertexArrays ( 1 , & vao );   

    glDeleteProgram ( program ) ;

}
void draw_coordinateMarker( GLfloat tMatrxi [16] ) 
{

    glViewport( x, y,  width,  height );
    glLineWidth (5.0);
    glUseProgram( program );
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0] );
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

     	glUniformMatrix4fv( tMatrixLocation , 1, GL_FALSE, tMatrxi );

        glDrawArrays( GL_LINES , 0, 6 );

        glDisableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram (0);    
}
