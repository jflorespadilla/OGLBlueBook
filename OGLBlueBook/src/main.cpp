#pragma once
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include "../classes/GFXManager.h"

int main() {
    GFXManager gfxM;
    gfxM.Start();
    gfxM.Run();

    return 0;
}
