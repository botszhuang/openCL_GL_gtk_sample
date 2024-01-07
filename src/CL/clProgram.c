#include "platFormStruct.h"
#include "miniTool.h"
#include "openCL_err.h"
void init_program( platFormStruct * p )
{
 cl_int err ;
 const unsigned int sourceListSzie = 1 ;

 char ** sourceList = calloc ( sourceListSzie , sizeof ( char * ) ) ;

 sourceList [0] = read_a_file ( "src/CL/kernel/dynamics/dynamics.cl" ) ;  

 p->program = clCreateProgramWithSource( p-> context, 
                                    sourceListSzie , ( const char ** ) sourceList ,
                                    NULL, &err);
                                    clErr ( err ) ;
   err = clBuildProgram( p->program , p->deviceNum , p-> device_list, NULL, NULL, NULL) ;
         clErr ( err ) ;

 for ( unsigned int i = 0 ; i < sourceListSzie ; i++  ) {
   free ( sourceList [i] ); 
 }
 free ( sourceList ) ;
}
void free_program ( platFormStruct * p  ){
  clErr ( clReleaseProgram( p->program ) ) ;
}