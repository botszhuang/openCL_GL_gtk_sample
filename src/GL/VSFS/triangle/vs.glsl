#version 460 core                                                  
                                                                   
layout(location = 0) in vec4 position;                                                  
                                                                   
out VS_OUT                                                         
{                                                                  
    vec4 color;                                                    
} vs_out;                                                          


layout(location = 0) uniform mat4 tMatrix ;

void main(void)                                                    
{                                                                  
    gl_Position = tMatrix * position * vec4( 0.5, 0.5, 1.0, 1.0 );
	vs_out.color = position + 0.5 ;
}                                                                  
