#include "Shader.h"

Shader::Shader() {

}

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
    std::cout << "\n\n" << FilePath << " not found.\n\n\n";
    return false;
}

void Shader::CompileShaders() {
	// Stub
}
