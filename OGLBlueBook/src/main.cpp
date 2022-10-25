#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>
#include "../classes/GFXManager.h"

int main() {
    // Not using time now, but will figureout a way to use it
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();

    GFXManager gfxM;
    gfxM.Start();
    gfxM.Run();

    return 0;
}
