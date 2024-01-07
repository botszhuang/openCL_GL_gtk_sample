#include <math.h>
#include <time.h>
#include "cl_buffer_struct.h"

void set_momentum_data_at_cup_mem( cl_buffer_struct * m )
{
    unsigned int N = sqrt ( m->Num ) ;
    myDouble * data = ( myDouble * ) m->data ;
    double l = 0 ;

    srand ( time(NULL) ) ;
    int min = -200 ;
    int max =  200 ;

    for (unsigned int i = 0 , c = 0 ; i < N ; i++ ){
    for (unsigned int j = 0         ; j < N ; j++ , c++ ){

        data[c].x = rand() % (max - min + 1) + min ;
        data[c].y = rand() % (max - min + 1) + min ; 
        data[c].z = rand() % (max - min + 1) + min ;
        data[c].w = 1 ;

        l = sqrt ( (data[c].x * data[c].x) +  (data[c].y * data[c].y) +  (data[c].z * data[c].z) ) ;
        data[c].x /= l ;  
        data[c].y /= l ;  
        data[c].z /= l ;
    }}  
    
}