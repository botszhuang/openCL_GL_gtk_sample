#version 410

layout ( points ) in;
layout ( triangle_strip, max_vertices = 8 ) out;

in vec4 baseColour[];

out vec4 colour;

uniform mat4 tMatrix ;

void main(void){

    float l = 0.3 ;
	colour = baseColour[0]  ;
	
	vec4 offset = vec4(-l, l, 1.0, 0.0);
	vec4 vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = tMatrix * vertexPos;
	EmitVertex();
	
	offset = vec4(-l, -l, 1.0, 0.0);
	vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = tMatrix * vertexPos;
	EmitVertex();
	
	offset = vec4(l, l, 1.0, 0.0);
	vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = tMatrix * vertexPos;
	EmitVertex();
		
	offset = vec4(l, -l, 1.0, 0.0);
	vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = tMatrix * vertexPos;
	EmitVertex();

	EndPrimitive();

}