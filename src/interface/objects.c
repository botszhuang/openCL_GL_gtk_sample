#include "checkMutex.h"
#include "cl_buffer_struct.h"
#include "miniTool.h"
#include "checkMutex.h"

static GLuint program ;
static GLint tMatrixLocation ;
static GLuint vao ;

static pthread_mutex_t glBufferData_mutex = PTHREAD_MUTEX_INITIALIZER ;

GLuint set_shader( char * file , GLenum shaderType )
{ 
 GLuint shader = glCreateShader( shaderType );
 char * source = read_a_file( file );  
 glShaderSource( shader , 1, (const char **) & source, NULL);
 free ( source ) ;
 glCompileShader ( shader ) ;
 shaderLog ( shader ) ;
 return shader ;
}
void free_shader ( GLuint program , GLuint shader )
{
 glDetachShader ( program, shader );
 glDeleteShader( shader ) ;    
}
GLuint set_program()
{
    GLuint program = glCreateProgram();

    GLuint vertexShader   = set_shader ( "src/interface/gl_vs.glsl" , GL_VERTEX_SHADER   );
    GLuint geometryShader = set_shader ( "src/interface/gl_gs.glsl" , GL_GEOMETRY_SHADER );
    GLuint fragmentShader = set_shader ( "src/interface/gl_fs.glsl" , GL_FRAGMENT_SHADER );

	glAttachShader( program, vertexShader   );
	glAttachShader( program, geometryShader );
	glAttachShader( program, fragmentShader );

	glLinkProgram ( program );
    glUseProgram  ( program );

	/* the individual shaders can be detached and destroyed */
    free_shader ( program , vertexShader   );     
    free_shader ( program , geometryShader );     
    free_shader ( program , fragmentShader );     

	return program ;
}

void init_objects( )
{
    program = set_program () ;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    tMatrixLocation = glGetUniformLocation( program , "tMatrix");
}
void free_objects()
{
    glDeleteVertexArrays ( 1 , & vao );

    glDeleteProgram ( program ) ;

    int err = pthread_mutex_destroy( & glBufferData_mutex );  
    checkResults("pthread_mutex_destroy()\n", err );
}
void draw_objects( GLfloat tMatrxi [16] , 
                   gl_cl_buffer_struct grid ,
                   gl_cl_buffer_struct momentum  )
{
    int err ;

    glUseProgram( program );
        glBindBuffer(GL_ARRAY_BUFFER, grid.gl );
            err = pthread_mutex_lock(  & glBufferData_mutex  ); checkResults("pthread_mutex_lock()\n", err );
        glBufferData (GL_ARRAY_BUFFER, grid.bytes    , grid.data     , GL_STATIC_DRAW);
            err = pthread_mutex_unlock(  & glBufferData_mutex  ); checkResults("pthread_mutex_unlock()\n", err );
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, momentum.gl );
            err = pthread_mutex_lock(  & glBufferData_mutex  ); checkResults("pthread_mutex_lock()\n", err );
        glBufferData (GL_ARRAY_BUFFER, momentum.bytes, momentum.data , GL_STATIC_DRAW);
            err = pthread_mutex_unlock(  & glBufferData_mutex  ); checkResults("pthread_mutex_unlock()\n", err );
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(1);

 	    glUniformMatrix4fv( tMatrixLocation , 1, GL_FALSE, tMatrxi );

        glDrawArrays( GL_POINTS , 0, grid.Num );

        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram (0);        
}
