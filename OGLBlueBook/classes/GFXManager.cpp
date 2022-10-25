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
    glDeleteVertexArrays(1, &m_vertex_array_object);
    glDeleteProgram(m_rendering_program);

    glfwTerminate();
}

void GFXManager::Start() {
    if (!m_glfwFlag) {

        // Need to make a getter function for shaders. This works for now.
        const GLchar* VS_Source[] = {
            "#version 450 core                                                                         \n"
            "void main (void) {                                                                           \n"
            "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), \n"
            "                                                         vec4(-0.25, -0.25, 0.5, 1.0),\n"
            "                                                         vec4(0.25, 0.25, 0.5, 1.0)); \n"
            "   gl_Position = vertices[gl_VertexID];                         \n"
            " }                                                                                     \n"
        };

        const GLchar* FS_Source[] = {
            "#version 450 core                                             \n"
            "out vec4 color;                                                   \n"
            "void main (void) {                                               \n"
            "   color = vec4(0.0, 0.8, 1.0, 1.0);                     \n"
            " }                                                                          \n"
        };

        m_rendering_program = CompileShaders(VS_Source, FS_Source);
        glCreateVertexArrays(1, &m_vertex_array_object);
        glBindVertexArray(m_vertex_array_object);
    } // Add else case for error checking. Skipping for now.
    return;
}

void GFXManager::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        Renderer(0); // Currently not using time, but need to restructure to use time properly.

        glfwSwapBuffers(m_window);

        glfwPollEvents();
        //t1 = t2;
        //t2 = std::chrono::steady_clock::now();
    }
}

GLuint GFXManager::CompileShaders(const GLchar** vertex_shader_source, const GLchar** fragment_shader_source) {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

void GFXManager::Renderer(float dt) {
    GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, color);
    glUseProgram(m_rendering_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
