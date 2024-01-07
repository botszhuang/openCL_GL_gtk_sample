#include <math.h>

#include "rotation_matrix_struct.h"

#define ROTATION_MATRIX( res, c1, c2, c3, s1, s2, s3 )\
{\
  float c3c2 = c3 * c2;\
  float s3c1 = s3 * c1;\
  float c3s2s1 = c3 * s2 * s1;\
  float s3s1 = s3 * s1;\
  float c3s2c1 = c3 * s2 * c1;\
  float s3c2 = s3 * c2;\
  float c3c1 = c3 * c1;\
  float s3s2s1 = s3 * s2 * s1;\
  float c3s1 = c3 * s1;\
  float s3s2c1 = s3 * s2 * c1;\
  float c2s1 = c2 * s1;\
  float c2c1 = c2 * c1;\
  \
  res[0] = c3c2;  res[4] = s3c1 + c3s2s1;  res[8] = s3s1 - c3s2c1; res[12] = 0.0;\
  res[1] = -s3c2; res[5] = c3c1 - s3s2s1;  res[9] = c3s1 + s3s2c1; res[13] = 0.0;\
  res[2] = s2;    res[6] = -c2s1;         res[10] = c2c1;          res[14] = 0.0;\
  res[3] = 0.0;   res[7] = 0.0;           res[11] = 0.0;           res[15] = 1.0;\
}


void get_rotaion_matrix_cos_sin ( float tMatrix [ 16 ] ,
                                  rotation_matrix_cos_sin_struct a ) {
  #define res (tMatrix)
  #define c1 (a.cosx)
  #define c2 (a.cosy)
  #define c3 (a.cosz)
  #define s1 (a.sinx)
  #define s2 (a.siny)
  #define s3 (a.sinz) 
    ROTATION_MATRIX( res, c1, c2, c3, s1, s2, s3 ) ;
  #undef c1 
  #undef c2 
  #undef c3 
  #undef s1 
  #undef s2 
  #undef s3
  #undef res   
}

void get_rotaion_matrix (  float tMatrix [ 16 ] ,
                           rotation_angle_struct a )
{
  float x = a.phi   * ( M_PI / 180.0 );
  float y = a.theta * ( M_PI / 180.0 );
  float z = a.psi   * ( M_PI / 180.0 );

  float c1 = cosf (x), s1 = sinf (x);
  float c2 = cosf (y), s2 = sinf (y);
  float c3 = cosf (z), s3 = sinf (z);

  ROTATION_MATRIX( tMatrix , c1, c2, c3, s1, s2, s3 ) ;
 
}
#undef ROTATION_MATRIX
