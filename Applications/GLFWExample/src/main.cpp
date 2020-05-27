
#include <Core/Log.hpp>
#include "GLFWExample.hpp"

int main() {
    Log::init();

    GLFWExample app;
    app.run();
    return 0;
}