#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>

void render(std::chrono::duration<float> dt);

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        render(t2-t1);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        t1 = t2;
        t2 = std::chrono::steady_clock::now();
    }

    glfwTerminate();
    return 0;
}

void render(std::chrono::duration<float> dt) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(cos(dt.count()) * 1.0f, cos(dt.count()) * 0.5f, cos(dt.count()) * 0.5f, 0.0f);
}