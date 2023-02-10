#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

class GFXManager
{
public:
	GFXManager();
	~GFXManager();
	void Start();
	void Run();
	void Renderer(float dt);
	std::string GetShader(const char* fileName);
	GLuint CompileShaders(std::vector<std::string>& shaders);

private:
	void CheckShaderCompilation(GLuint& shader);

	GLuint m_rendering_program;
	GLuint m_vertex_array_object;
	GLFWwindow* m_window;

	bool m_glfwFlag;
};

