
#include <Core/Log.hpp>
#include "GLFWExample.hpp"

int main() {
    Log::init();
    APP_INFO("Logger initialized.");
    ENGINE_INFO("Logger initialized.");

    GLFWExample app;
    app.run();
    return 0;
}