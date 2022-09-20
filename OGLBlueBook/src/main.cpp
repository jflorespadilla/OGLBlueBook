#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>

static const GLchar* vertex_shader_source[] = {
    "#version 450 core                                             \n"
    "void main (void) {                                               \n"
    "   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);           \n"
    " }                                                                          \n"
};

static const GLchar* fragment_shader_source[] = {
    "#version 450 core                                             \n"
    "out vec4 color;                                                   \n"
    "void main (void) {                                               \n"
    "   color = vec4(0.0, 0.8, 1.0, 1.0);                     \n"
    " }                                                                          \n"
};
void render(float dt);

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
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        render((t2-t1).count());

        glfwSwapBuffers(window);

        glfwPollEvents();
        t1 = t2;
        t2 = std::chrono::steady_clock::now();
    }

    glfwTerminate();
    return 0;
}

void render(float dt) {
    GLfloat color[] = { cos(dt) * 0.5f + 0.5f,
                                   sin(dt) * 0.5f + 0.5f,
                                   0.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, color);
}