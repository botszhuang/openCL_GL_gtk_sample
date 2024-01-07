#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "mytype.h"

#define OPENFILEERROR(  filename ){\
	printf( "cannot open %s in FILE %s at line %d)\n" , filename , __FILE__ , __LINE__ ) ;\
	exit ( 1 ) ;\
}
char * read_a_file( const char* filename )
{
	struct stat st ;

	stat( filename, &st );
	if ( st.st_size <= 0 ) { OPENFILEERROR(filename) ; };

	FILE *  fp = fopen( filename, "r") ;
	if ( fp == NULL ) { OPENFILEERROR(filename) ; };

	char * src = calloc ( st.st_size + 1 , sizeof ( char ) ) ;
	size_t fread_out = fread ( src, sizeof(char), st.st_size, fp ) ;
	if ( fread_out != st.st_size ) { OPENFILEERROR (filename) ; }

	src[ st.st_size ] = '\0';

    fclose ( fp ) ;

	return src ;
}

#undef OPENFILEERROR

void shaderLog( GLuint shader )
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = malloc ( sizeof(GLchar) * maxLength ) ;
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		printf("%s\n", errorLog);
		free(  errorLog ) ;
		glDeleteShader ( shader ) ;
	}
}

void DumpInfo(void)
{
	printf("Vendor: %s\n"  , glGetString (GL_VENDOR));
	printf("Renderer: %s\n", glGetString (GL_RENDERER));
	printf("Version: %s\n" , glGetString (GL_VERSION));
	printf("GLSL: %s\n"    , glGetString (GL_SHADING_LANGUAGE_VERSION));
}
