__kernel                                   
void dynamics_kernel( __global float4 * Bin ,  __global float4 * Min , const unsigned int Nin )       
{                                          
    const unsigned int gId = get_global_id(0) ; 
    const unsigned int N = Nin ;

    if ( gId >= N ) { return ; }

    const unsigned int gGAP = get_global_size ( 0 ) ;
    float3 M ;
    float3 B ;
    B.x = Bin[0].x ; 
    B.y = Bin[0].y ;
    B.z = Bin[0].z ;

    if ( B.x == 0 ) {
    if ( B.y == 0 ) {
    if ( B.z == 0 ) {
        return ;  
    }}}

    float3 Brot ;
    float3 b ;
    float Bamp ;
    float a = 0.1 ;

    const float dt =  0.01 ;
    float w    = 0 ;
    float cosw = 0 ;
    float sinw = 0 ;
    float U    = 0 ; 

    float R [ 9 ] ;
    float bxU , byU , bzU ;
    float bxSinw , bySinw , bzSinw ;

    for ( unsigned int gi = gId ; gi < N ; gi = gi + gGAP ){ 

        M = ( float3 ) ( Min[gi] .xyz ) ;

        Brot.x =  ( M.y * B.z ) - ( M.z * B.y ) ; 
        Brot.y =  ( M.z * B.x ) - ( M.x * B.z ) ; 
        Brot.z =  ( M.x * B.y ) - ( M.y * B.x ) ; 
        Brot *= a ; 
        Brot += B ;

        Bamp = sqrt ( (Brot.x * Brot.x) +  (Brot.y * Brot.y) +  (Brot.z * Brot.z) ) ;
        if ( Bamp == 0 ) { continue ; }
        
        b.x = Brot.x / Bamp ;
        b.y = Brot.y / Bamp ;
        b.z = Brot.z / Bamp ;


        w = dt * Bamp ;
        cosw = cos ( w ) ;
        sinw = sin ( w ) ;
        U    = 1 - cosw  ; 

        bxU = b.x * U ;
        byU = b.y * U ;
        bzU = b.z * U ;

        bxSinw = b.x * sinw ;
        bySinw = b.y * sinw ;
        bzSinw = b.z * sinw ; 

        R [0] =  ( b.x * bxU ) +   cosw ;   R [3] =  ( b.x * byU ) - bzSinw ;   R [6] =  ( b.x * bzU ) + bySinw ;
        R [1] =  ( b.y * bxU ) + bzSinw ;   R [4] =  ( b.y * byU ) +   cosw ;   R [7] =  ( b.y * bzU ) - bxSinw ;
        R [2] =  ( b.z * bxU ) - bySinw ;   R [5] =  ( b.z * byU ) + bxSinw ;   R [8] =  ( b.z * bzU ) +   cosw ;

        Min [ gi ].x =  ( R [0] * M.x ) + ( R[3] * M.y ) + ( R[6] * M.z ) ; 
        Min [ gi ].y =  ( R [1] * M.x ) + ( R[4] * M.y ) + ( R[7] * M.z ) ; 
        Min [ gi ].z =  ( R [2] * M.x ) + ( R[5] * M.y ) + ( R[8] * M.z ) ; 
        
    }   
    return ;                        
}       
                                 
