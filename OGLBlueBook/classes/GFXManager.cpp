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
        std::string shaderSources[5];
        // Need to make a getter function for shaders. This works for now.
        shaderSources[0] = GetShader("shaders/vs.shader");

        shaderSources[1] = GetShader("shaders/fs.shader");

        shaderSources[2] = GetShader("shaders/tcs.shader");

        shaderSources[3] = GetShader("shaders/tes.shader");

        shaderSources[4] = GetShader("shaders/geo.shader");

        // TODO - Rework this portion. I need to make it easier to feed different types of shaders to one compile shader function.
        m_rendering_program = CompileShaders(shaderSources);
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

GLuint GFXManager::CompileShaders(std::string* shaders) {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint tessc_shader;
    GLuint tesse_shader;
    GLuint geo_shader;
    GLuint program;

    const GLchar* vertex_shader_source = shaders[0].c_str();
    const GLchar* fragment_shader_source = shaders[1].c_str();
    const GLchar* tcs_shader_source = shaders[2].c_str();
    const GLchar* tes_shader_source = shaders[3].c_str();
    const GLchar* geo_shader_source = shaders[4].c_str();

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    tessc_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tessc_shader, 1, &tcs_shader_source, NULL);
    glCompileShader(tessc_shader);

    tesse_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tesse_shader, 1, &tes_shader_source, NULL);
    glCompileShader(tesse_shader);

    geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geo_shader, 1, &geo_shader_source, NULL);
    glCompileShader(geo_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteShader(tessc_shader);
    glDeleteShader(tesse_shader);
    glDeleteShader(geo_shader);

    return program;
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
    const GLfloat color[] = { (float)sin(dt) * 0.5f + 0.5f, (float)cos(dt) * 0.5f + 0.5f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    glUseProgram(m_rendering_program);

    GLfloat attrib[] = { (float)sin(dt) * 0.5f , (float)cos(dt) * 0.6f, 0.0f, 0.0f };
    glVertexAttrib4fv(0, attrib);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
