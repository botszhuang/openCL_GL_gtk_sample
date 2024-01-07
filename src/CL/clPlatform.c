
#include "platFormStruct.h"
#include "miniTool.h"


#define printPlatformProfile( platform,INFO,string){\
  err = clGetPlatformInfo ( platform , INFO , charBufferSize , charBuffer , NULL ) ;\
  clErr ( err ) ;\
  printf (  "      %s: %s\n", string, charBuffer ) ;\
}
inline static void printAllPlatformProfile( cl_platform_id * p , const unsigned int N , unsigned int charBufferSize, char * charBuffer ) 
{
    cl_int err ;

      for ( unsigned int i = 0; i < N ; i++)
      {
        printf ( "platform [%i]:\n" , i ) ;
        printPlatformProfile ( p[i] , CL_PLATFORM_PROFILE    , "CL_PLATFORM_PROFILE" ) ;
        printPlatformProfile ( p[i] , CL_PLATFORM_VERSION    , "CL_PLATFORM_VERSION" ) ;
        printPlatformProfile ( p[i] , CL_PLATFORM_NAME       , "CL_PLATFORM_NAME"    ) ;
        printPlatformProfile ( p[i] , CL_PLATFORM_VENDOR     , "CL_PLATFORM_VENDOR"  ) ;
        printPlatformProfile ( p[i] , CL_PLATFORM_EXTENSIONS , "CL_PLATFORM_EXTENSIONS" ) ;
      }
}
#define printDeviceProfile( device,INFO,string){\
  err = clGetDeviceInfo ( device , INFO , charBufferSize , charBuffer , NULL ) ;\
  clErr ( err ) ;\
  printf (  "      %s: %s\n", string, charBuffer ) ;\
}
inline static void printAllDeviceProfile( cl_device_id * d , const unsigned int N , unsigned int charBufferSize, char * charBuffer ) 
{
    cl_int err ;

      for ( unsigned int i = 0; i < N ; i++)
      {
        printf ( "  device [%i]:\n" , i ) ;
        printDeviceProfile ( d[i] , CL_DEVICE_PROFILE    , "CL_DEVICE_PROFILE" ) ;
        printDeviceProfile ( d[i] , CL_DEVICE_VERSION    , "CL_DEVICE_VERSION" ) ;
        printDeviceProfile ( d[i] , CL_DEVICE_NAME       , "CL_DEVICE_NAME"    ) ;
        printDeviceProfile ( d[i] , CL_DEVICE_VENDOR     , "CL_DEVICE_VENDOR"  ) ;
        printDeviceProfile ( d[i] , CL_DEVICE_EXTENSIONS , "CL_DEVICE_EXTENSIONS" ) ;
      }
}
#define printDeviceProfileUINT( context, INFO , str ){\
  err = clGetContextInfo( context , INFO, sizeof( uIntNumber ) , &uIntNumber, NULL ) ; \
  clErr ( err ) ;\
  printf ( "%s = %i\n" , str , uIntNumber ) ;\
}

void init_platForm ( platFormStruct * p ) 
{

  const unsigned int charBufferSize = 1024 * sizeof ( char ) ;
  char * charBuffer = malloc ( charBufferSize ) ;

  cl_int err ;

  err = clGetPlatformIDs(0, NULL, & p->platformNum);
      p->platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id)* p->platformNum);
      err = clGetPlatformIDs( p->platformNum, p->platforms, NULL);
      print_separation_line ;
      printAllPlatformProfile( p->platforms , p->platformNum , charBufferSize , charBuffer );
  print_separation_line ;

      
  err = clGetDeviceIDs( p-> platforms[0], CL_DEVICE_TYPE_GPU, 0,NULL, &p-> deviceNum);
      p->device_list = (cl_device_id *)  malloc(sizeof(cl_device_id)*p->deviceNum);
      err = clGetDeviceIDs( p-> platforms[0],CL_DEVICE_TYPE_GPU, p-> deviceNum, p-> device_list, NULL);



const cl_context_properties my_context_properties[] = {
    CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
    CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
    CL_CONTEXT_PLATFORM, (cl_context_properties)p->platforms[0],
    0
    };
  

  p-> context = clCreateContext( my_context_properties , p-> deviceNum, p-> device_list, NULL, NULL, &err);
  clErr ( err ) ;

      unsigned int uIntNumber = 0 ;    
      printDeviceProfileUINT( p->context, CL_CONTEXT_REFERENCE_COUNT , "context refernce count" ) ;
      printDeviceProfileUINT( p->context, CL_CONTEXT_NUM_DEVICES , "number of devices in the context" ) ;

      cl_device_id * deviceId = malloc ( uIntNumber * sizeof ( cl_device_id ) ) ;
      err = clGetContextInfo( p->context , CL_CONTEXT_DEVICES, sizeof( cl_device_id ) * uIntNumber , deviceId, NULL ) ;  clErr ( err ) ;
      puts ( "device profile in the context:" );
      printAllDeviceProfile( deviceId , uIntNumber , charBufferSize, charBuffer ) ;
      free ( deviceId ) ;
  print_separation_line ;                    

  free ( charBuffer ) ;    

}
#undef printDeviceProfileUINT
#undef printDeviceProfile
#undef printPlatformProfile

void free_platForm ( platFormStruct p ) {
  
  cl_int err ;

  err = clReleaseContext( p. context);
  
  free( p. platforms);
  free( p. device_list) ;

}