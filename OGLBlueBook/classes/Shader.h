#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <gl/glew.h>

enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1, TC = 2, T = 3, G = 4 
};

class Shader
{
public:
	Shader();
	~Shader();
	void CreateShader(std::string FilePath);
	void CompileShaders();

private:
	std::vector<std::string> ShaderSourceList;
	std::vector<GLuint> CompiledShaders;
};

