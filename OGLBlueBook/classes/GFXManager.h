#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

class GFXManager
{
public:
	GFXManager();
	~GFXManager();
	void Start();
	void Run();
	void Renderer(float dt);
	GLuint CompileShaders(const GLchar* vertex_shader_source , const GLchar* fragment_shader_source);
	const char* GetShader(const char* fileName);

private:
	GLuint m_rendering_program;
	GLuint m_vertex_array_object;
	GLFWwindow* m_window;

	bool m_glfwFlag;
};

