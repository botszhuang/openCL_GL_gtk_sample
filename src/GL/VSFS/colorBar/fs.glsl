#version 460 core                                                  
                                                                   
out vec4 color;                                                    
                                                                   
in vec3 vsOutcolor;                                                                                                              
                                                          
                                                                   
void main(void)                                                    
{                              
    color = vec4 ( vsOutcolor , 1 ) ;
}                                                                  
