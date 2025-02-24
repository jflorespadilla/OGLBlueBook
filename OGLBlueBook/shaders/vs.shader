#Shader vertex
#version 450 core

in vec4 position;
in vec4 color;

out VS_OUT {
	vec4 color;
} vs_out;

layout (location = 0) uniform mat4 mv_matrix;
layout (location = 1) uniform mat4 proj_matrix;

void main (void) {
	gl_Position = proj_matrix * mv_matrix * position;
	vs_out.color = color;
}