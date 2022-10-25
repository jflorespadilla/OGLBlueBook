#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class GFXManager
{
public:
	GFXManager();
	~GFXManager();
	void Renderer();

private:
	GLuint m_rendering_program;
	GLuint m_vertex_array_object;
	GLFWwindow* m_window;
};

