#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>
//#include <GFXManager>

static const GLchar* vertex_shader_source[] = {
    "#version 450 core                                                                         \n"
    "void main (void) {                                                                           \n"
    "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), \n"
    "                                                         vec4(-0.25, -0.25, 0.5, 1.0),\n"
    "                                                         vec4(0.25, 0.25, 0.5, 1.0)); \n"
    "   gl_Position = vertices[gl_VertexID];                         \n"
    " }                                                                                     \n"
};

static const GLchar* fragment_shader_source[] = {
    "#version 450 core                                             \n"
    "out vec4 color;                                                   \n"
    "void main (void) {                                               \n"
    "   color = vec4(0.0, 0.8, 1.0, 1.0);                     \n"
    " }                                                                          \n"
};

GLuint rendering_program;
GLuint vertex_array_object;

// Most important function to import
void render(float dt);
GLuint compile_shaders();

int main() {
    GLFWwindow* window;
   
    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gl3wInit();

    rendering_program = compile_shaders();
    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        render((t2-t1).count());

        glfwSwapBuffers(window);

        glfwPollEvents();
        t1 = t2;
        t2 = std::chrono::steady_clock::now();
    }

    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);

    glfwTerminate();
    return 0;
}

void render(float dt) {
    GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, color);
    glUseProgram(rendering_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint compile_shaders() {
    // Make this into class variables
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