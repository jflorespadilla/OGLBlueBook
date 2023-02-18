#include "GFXManager.h"

GFXManager::GFXManager():
m_rendering_program(0),
m_vertex_array_object(0),
m_window(NULL),
m_glfwFlag(false)
{
    if (!glfwInit()) {
        m_glfwFlag = true;
    }

    m_window = glfwCreateWindow(640, 480, "Hola", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        m_glfwFlag = true;
    }
    else {
        glfwMakeContextCurrent(m_window);
        gl3wInit();
    }
}

GFXManager::~GFXManager() {
    if (!m_glfwFlag) {
        glDeleteVertexArrays(1, &m_vertex_array_object);
        glDeleteProgram(m_rendering_program);

        glfwTerminate();
    }
}

void GFXManager::Start() {
    if (!m_glfwFlag) {
        std::vector<std::string> shaderSrcs;

        shaderSrcs.push_back(GetShader("shaders/vs.shader"));
        
        //shaderSrcs.push_back(GetShader("shaders/tcs.shader"));

        //shaderSrcs.push_back(GetShader("shaders/tes.shader"));

        //shaderSrcs.push_back(GetShader("shaders/geo.shader"));

        shaderSrcs.push_back(GetShader("shaders/fs.shader"));

        m_rendering_program = CompileShaders(shaderSrcs);
        glCreateVertexArrays(1, &m_vertex_array_object);
        glBindVertexArray(m_vertex_array_object);
    }
    else {
        std::cout << "Error in creating window!";
    }
    return;
}

void GFXManager::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        Renderer(glfwGetTime());
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

GLuint GFXManager::CompileShaders(std::vector<std::string>& shaders) {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint tessc_shader;
    GLuint tesse_shader;
    GLuint geo_shader;
    GLuint program;

    program = glCreateProgram();

    std::vector<std::string>::iterator shaderIt;
    std::vector<std::string>::iterator lastElement = shaders.end() - 1;
    int count = 0;

    const GLchar* fragment_shader_source;
    const GLchar* vertex_shader_source;
    const GLchar* tcs_shader_source = NULL;
    const GLchar* tes_shader_source = NULL;
    const GLchar* geo_shader_source = NULL;

    for (shaderIt = shaders.begin(); shaderIt != shaders.end(); shaderIt++) {
        if (count > 0 && shaderIt != lastElement) {
            if (count == 1) {
                tcs_shader_source = shaderIt->c_str();
            }
            if (count == 2) {
                tes_shader_source = shaderIt->c_str();
            }
            if (count == 3) {
                geo_shader_source = shaderIt->c_str();
            }
        }
        if (count == 0) {
            vertex_shader_source = shaderIt->c_str();
        }
        if (shaderIt == lastElement) {
            fragment_shader_source = shaderIt->c_str();
        }
        count++;
    }

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    CheckShaderCompilation(vertex_shader);
    glAttachShader(program, vertex_shader);

    if (tcs_shader_source != NULL) {
        tessc_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessc_shader, 1, &tcs_shader_source, NULL);
        glCompileShader(tessc_shader);
        CheckShaderCompilation(tessc_shader);
        glAttachShader(program, tessc_shader);
    }

    if (tes_shader_source != NULL) {
        tesse_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tesse_shader, 1, &tes_shader_source, NULL);
        glCompileShader(tesse_shader);
        CheckShaderCompilation(tesse_shader);
        glAttachShader(program, tesse_shader);
    }

    if (geo_shader_source != NULL) {
        geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geo_shader, 1, &geo_shader_source, NULL);
        glCompileShader(geo_shader);
        CheckShaderCompilation(geo_shader);
        glAttachShader(program, geo_shader);
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    CheckShaderCompilation(fragment_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (tcs_shader_source != NULL) {
        glDeleteShader(tessc_shader);
    }
    if (tes_shader_source != NULL) {
        glDeleteShader(tesse_shader);
    }
    if (geo_shader_source != NULL) {
        glDeleteShader(geo_shader);
    }

    return program;
}

void GFXManager::CheckShaderCompilation(GLuint& shader) {
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        for (int i = 0; i < maxLength; i++) {
            std::cout << errorLog[i];
        }
    }
    else {
        std::cout << "Success!!!\n\n";
    }
}

std::string GFXManager::GetShader(const char* filePath) {
    std::fstream fileStream;
    std::string line;
    std::string content;

    fileStream.open(filePath, std::ios::in);
    if (fileStream.is_open()) {
        while (std::getline(fileStream, line)) {
            if (line.length() == 0) {
                content.append("\n");
            }
            else {
                content.append(line);
            }
        }
        fileStream.close();
    }
    return content;
}

void GFXManager::Renderer(float dt) {
    const GLfloat BGcolor[] = { (float)sin(dt) * 0.5f + 0.5f, (float)cos(dt) * 0.5f + 0.5f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, BGcolor);
    glUseProgram(m_rendering_program);

    GLfloat attrib[] = { (float)sin(dt) * 0.5f , (float)cos(dt) * 0.6f, 0.0f, 0.0f };
    glVertexAttrib4fv(0, attrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
