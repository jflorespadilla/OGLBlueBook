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

        // Need to make a getter function for shaders. This works for now.
        std::string VS_Source = GetShader("shaders/vs.shader");

        std::string FS_Source =  GetShader("shaders/fs.shader");

        m_rendering_program = CompileShaders(VS_Source.c_str(), FS_Source.c_str());
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

GLuint GFXManager::CompileShaders(const GLchar* vertex_shader_source, const GLchar* fragment_shader_source) {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

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
    const GLfloat color[] = { (float)sin(dt) * 0.5f + 0.5f, (float)cos(dt) * 0.5f + 0.5f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    glUseProgram(m_rendering_program);

    GLfloat attrib[] = { (float)sin(dt) * 0.5f + 0.5f, (float)cos(dt) * 0.5f + 0.6f, 0.0f, 0.0f };
    glVertexAttrib4fv(0, attrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
