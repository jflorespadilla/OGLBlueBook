#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <gl/gl3w.h>

enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1, TC = 2, T = 3, G = 4 
};

class Shader
{
public:
	Shader();
	~Shader();
	bool GetShaderSource(std::string FilePath);
	void CompileShaders();
	GLuint GetShaderID(ShaderType shaderType);


private:
	GLuint CheckShaderCompilation(GLuint& shader);

	std::unordered_map<ShaderType, std::string> ShaderSourceList;
	std::unordered_map<ShaderType, GLuint> CompiledShaders;
};

