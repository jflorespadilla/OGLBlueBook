#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>

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
        render(t2.time_since_epoch().count());

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