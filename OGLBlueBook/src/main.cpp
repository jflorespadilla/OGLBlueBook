#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>
#include <random>

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
    std::default_random_engine rng(dt.count());
    std::uniform_int_distribution<int> dist(1, 100);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(cos(dist(rng)) * 1.0f, cos(dist(rng)) * 0.5f, cos(dist(rng)) * 0.5f, 0.0f);
}