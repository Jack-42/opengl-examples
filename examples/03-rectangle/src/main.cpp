#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "RectangleRenderer.hpp"

int main()
{
    try {
        RectangleRenderer renderer;
        Window window("03 - Rectangle", 800, 800, &renderer);
        window.runRenderLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
