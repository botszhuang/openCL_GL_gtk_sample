#ifndef GEOMETRY_MATRIX_H
#define GEOMETRY_MATRIX_H

#include "rotation_matrix_struct.h"
void get_rotaion_matrix         ( float tMatrix [ 16 ] ,  rotation_angle_struct a) ;
void get_rotaion_matrix_cos_sin ( float tMatrix [ 16 ] , rotation_matrix_cos_sin_struct a ) ;

void get_scale_matrix ( float m [16] , float x , float y , float z ) ;
#endif