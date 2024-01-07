#include "my_CL_GL.h"
#include "miniTool.h"

GLuint init_vsfsProgram( const char * vsfile , const char * fsfile )
{
	GLuint vertexShader  = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	char * vsSource = read_a_file( vsfile );
	char * fsSource = read_a_file( fsfile );

	glShaderSource( vertexShader , 1, (const char **) & vsSource, NULL);
	glShaderSource( fragmentShader , 1, (const char **) & fsSource, NULL);

	free(vsSource);
	free(fsSource);

	glCompileShader( vertexShader   );
	glCompileShader( fragmentShader );

	shaderLog( vertexShader   );
	shaderLog( fragmentShader );

    GLuint program = glCreateProgram();
	glAttachShader( program, vertexShader   );
	glAttachShader( program, fragmentShader );

	glLinkProgram ( program );

    glUseProgram ( program );

	 /* the individual shaders can be detached and destroyed */
    glDetachShader ( program, vertexShader   );
    glDetachShader ( program, fragmentShader );
	glDeleteShader( vertexShader   ) ;
	glDeleteShader( fragmentShader ) ;

	return program ;

}

