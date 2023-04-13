#include "Shader.h"

Shader::Shader() {

}
//write second constructor

Shader::~Shader() {

}

bool Shader::GetShaderSource(std::string FilePath) {
    std::fstream fileStream;
    std::string line;
    std::stringstream content;
    ShaderType ST = ShaderType::NONE;

    fileStream.open(FilePath, std::ios::in);
    if (fileStream.is_open()) {
        while (std::getline(fileStream, line)) {
            if (line.find("#Shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    ST = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    ST = ShaderType::FRAGMENT;
                }
                else if (line.find("control") != std::string::npos) {
                    ST = ShaderType::TC;
                }
                else if (line.find("tess") != std::string::npos) {
                    ST = ShaderType::T;
                }
                else if (line.find("geo") != std::string::npos) {
                    ST = ShaderType::G;
                }
            }
            else { 
                content << line << "\n"; 
            }
        }
        fileStream.close();
        ShaderSourceList.insert(std::pair<ShaderType, std::string>(ST, content.str()));
        return true;
    }
    std::cout << "\n\n" << FilePath << " not found. Shader Class Report.\n\n\n";
    return false;
}

void Shader::CompileShaders() {
    std::unordered_map<ShaderType, std::string>::iterator cursor = ShaderSourceList.begin();
    const GLchar* ShaderSource;
    GLuint shaderID = 0;
    ShaderType index;

    for (cursor; cursor != ShaderSourceList.end(); cursor++) {
        index = cursor->first;
        ShaderSource = cursor->second.c_str();
        
        switch (index) {
            case ShaderType::VERTEX:
                shaderID = glCreateShader(GL_VERTEX_SHADER);
                std::cout << "\nVertex Shader ID created\n";
                break;
            case ShaderType::FRAGMENT:
                shaderID = glCreateShader(GL_FRAGMENT_SHADER);
                std::cout << "\nFragment Shader ID created\n";
                break;
            case ShaderType::TC:
                shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
                std::cout << "\nTesselation Control Shader ID created\n";
                break;
            case ShaderType::T:
                shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
                std::cout << "\nTesselation Evaluation Shader ID created\n";
                break;
            case ShaderType::G:
                shaderID = glCreateShader(GL_GEOMETRY_SHADER);
                std::cout << "\nGeometry Shader ID created\n";
                break;
            default:
                shaderID = NULL;
                std::cout << "\nInvalid Shader Delcaration! \n\tThis program needs a \"#Shader <Shader Type>\" declaration at the begining of the file.\n";
        }

        if (shaderID != NULL) {
            glShaderSource(shaderID, 1, &ShaderSource, NULL);
            glCompileShader(shaderID);
            if (CheckShaderCompilation(shaderID)) {
                CompiledShaders[index] = shaderID;
            }
            else {
                std::cout << "\nFailed to compile shader!!\n";
            }
        }
    }
}

GLuint Shader::GetShaderID(ShaderType shaderType) {
    std::unordered_map<ShaderType, GLuint>::iterator searchResult = CompiledShaders.find(shaderType);
    if (searchResult != CompiledShaders.end()) {
        return searchResult->second;
    }
    return NULL;
}

GLuint Shader::CheckShaderCompilation(GLuint& shader) {
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    // Write a log extraction function later. The old one that was in GFXManager was just not working.
    // I tried rewriting that dumb thing a few ways and the one time I got it to compile, it returned garbage.

    return success;
}
