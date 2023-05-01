#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class GFXManager
{
public:
	GFXManager();
	~GFXManager();
	void Start();
	void Run();
	void Renderer(float dt);
	GLuint CreateDefaultProgram();

private:
	GLuint m_rendering_program;
	GLuint m_vertex_array_object;
	Shader m_shaders;
	GLFWwindow* m_window;

	bool m_glfwFlag;

	// Model should happen sparately elsewhere
	glm::mat4 m_camera;
	glm::mat4 m_projection;

};

