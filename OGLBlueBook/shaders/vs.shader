#Shader vertex
#version 450 core

void main (void) {
	const vec4 verticies[3] = vec4[3] (vec4(0.25, -0.25, 0.5, 1.0),
															vec4(-0.25, -0.25, 0.5, 1.0),
															vec4(0.25, 0.25, 0.5, 1.0));
	gl_Position = verticies[gl_VertexID];
}