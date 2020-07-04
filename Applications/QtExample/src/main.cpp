
#include <Core/Utils/Log.hpp>
//#include <Minimal-Engine/Renderer.hpp>

int main() {
    stardust::core::utils::Log::init();

    // Renderer renderer(1200, 600);

    APP_INFO("Hello Qt world!");
    return 0;
}