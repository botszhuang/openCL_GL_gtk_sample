#include <math.h>
#include "cl_buffer_struct.h"

void set_grid_data_at_cup_mem ( cl_buffer_struct * grid )
{

    unsigned int N = sqrt ( grid->Num ) ;
    myDouble * gridData = ( myDouble * ) grid->data ;

    for (unsigned int i = 0 , c = 0 ; i < N ; i++ ){
    for (unsigned int j = 0         ; j < N ; j++ , c++ ){

        gridData[c].x = i - (N/2.0) ;  
        gridData[c].y = j - (N/2.0) ; 
        gridData[c].z = 0 ;
        gridData[c].w = 1 ;
    }}  

}

