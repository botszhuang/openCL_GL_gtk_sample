#version 460 core                                                  
                                                                   
layout(location = 0) in vec3 position ;                                                  
                                                                   
out VS_OUT                                                         
{                                                                  
    vec4 color;                                                    
} vs_out;                                                          

layout(location = 0) uniform mat4 tMatrix ;
                                                                                                                                                                             
void main(void)                                                    
{                                                                  
    gl_Position = tMatrix * vec4(position, 1.0) ;
	vs_out.color = vec4(position, 1.0) ;
}                                                                  
