#ifndef ROTATION_MATRIX_H
#define ROTATION_MATRIX_H

#include "mytype.h"
typedef struct 
{
    float  phi ;   //X_AXIS
    float  theta ; //Y_AXIS
    float  psi ;   //Z_AXIS
} rotation_angle_struct;
typedef struct 
{
  float  cosx, sinx ;
  float  cosy, siny ;
  float  cosz, sinz ;
} rotation_matrix_cos_sin_struct;
#endif