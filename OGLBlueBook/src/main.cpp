#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>
#include <random>

void render(std::chrono::duration<float> dt, std::default_random_engine& rng, std::uniform_int<int>& dist);

int main() {
    GLFWwindow* window;
    std::default_random_engine rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, 10);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        render(t2-t1, rng, dist);

        glfwSwapBuffers(window);

        glfwPollEvents();
        t1 = t2;
        t2 = std::chrono::steady_clock::now();
    }

    glfwTerminate();
    return 0;
}

void render(std::chrono::duration<float> dt, std::default_random_engine& rng, std::uniform_int<int>& dist) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(cos(dist(rng)), sin(dist(rng)), cos(dist(rng)), 0.0f);
}