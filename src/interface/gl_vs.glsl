#version 410


layout ( location = 0 ) in vec4 position;
layout ( location = 1 ) in vec4 colour;

out vec4 baseColour;

void main(void){

	gl_Position = position ;
	baseColour = colour; 

}
