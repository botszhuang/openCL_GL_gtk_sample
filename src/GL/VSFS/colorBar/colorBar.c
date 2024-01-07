#include "vsfsProgram.h"
#include "checkMutex.h"
#include <math.h>
#include <string.h>
#include "const_extern_parameter.h"
#include "variable_collection_struct.h"

static GLint x = 5 ;
static GLint y = 5 ;
static GLint width  = 10 ;
static GLint height = 10 ;

static GLuint vbo [2] = { 0 , 0 } ;
static GLuint vao = 0 ;
static GLuint program ;

static pthread_mutex_t gl_mutex = PTHREAD_MUTEX_INITIALIZER ;

static const float points[] = {
   1,  1,  0,
  -1,  1,  0,
  -1, -1,  0,
   1, -1,  0
};
static float color[12];
static unsigned int colorBytes ;
static unsigned int B_ampBytes ;
static void init_buffers(){

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers( 2, vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colorBytes , color, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
  
}

void init_colorBar()
{ 
    program = init_vsfsProgram( "src/GL/VSFS/colorBar/vs.glsl" , 
                                "src/GL/VSFS/colorBar/fs.glsl" ) ;
    init_buffers () ;

    width  = (int) ( windowSizeX /5.0 )  ;
    height = (int) ( windowSizeY /5.0 )  ;
    printf ( "axis: %d, %d , %d, %d\n", x, y, width, height ) ;

    colorBytes = 12 * sizeof ( float ) ;
    B_ampBytes =  3 * sizeof ( float ) ;

}
void free_colorBar()
{
    glDeleteBuffers      ( 2 ,   vbo );
    glDeleteVertexArrays ( 1 , & vao );   

    glDeleteProgram ( program ) ;

}
void draw_colorBar() 
{
    int err = pthread_mutex_lock(  & gl_mutex  );  checkResults("pthread_mutex_lock()\n", err );\
    memcpy( color , &(global_variable.B_amp), B_ampBytes ) ;
        err = pthread_mutex_unlock( & gl_mutex );  checkResults("pthread_mutex_unlock()\n", err );\

    float l = sqrt( color[0] * color[0] + ( color[1] * color[1] ) + ( color[2] * color[2] ) ) ;
    if ( l != 0 ) {
        color[0] /= l ;
        color[1] /= l ;
        color[2] /= l ;
    }

    
    memcpy( &(color[3]) , color, B_ampBytes ) ;
    memcpy( &(color[6]) , color, B_ampBytes ) ;
    memcpy( &(color[9]) , color, B_ampBytes ) ;

    printf ("B_amp: %.2f %.2f %.2f\n" , color[0] , color[1] , color[2] ) ;

    glViewport( width * 1.2 , height *0.5 ,  width *.5 ,  height *.5 );

    glUseProgram( program );
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0] );
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1] );
        glBufferData(GL_ARRAY_BUFFER, colorBytes ,  color, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(1);

        glDrawArrays( GL_TRIANGLE_FAN , 0, 4 );

        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram (0); 

}
