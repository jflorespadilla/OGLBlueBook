#include "Shader.h"

Shader::Shader() {

}

Shader::~Shader() {

}

bool Shader::GetShaderSource(std::string FilePath) {
    std::fstream fileStream;
    std::string line;
    std::stringstream content;

    fileStream.open(FilePath, std::ios::in);
    if (fileStream.is_open()) {
        while (std::getline(fileStream, line)) {
            content << line << "\n";
        }
        fileStream.close();
        ShaderSourceList.push_back(content.str());
        return true;
    }
    std::cout << "\n\n" << FilePath << " not found.\n\n\n";
    return false;
}

void Shader::CompileShaders() {
	// Stub
}
