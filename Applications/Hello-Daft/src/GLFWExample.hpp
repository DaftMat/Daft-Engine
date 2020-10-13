//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <Core/Utils/BaseApplication.hpp>
#include <Engine/Renderer/Renderer.hpp>

#include "GLFWWindow.hpp"

namespace daft::app {
class ENGINE_API GLFWExample : public core::BaseApplication<GLFWWindow> {
   public:
    GLFWExample();

    ~GLFWExample() override = default;

    void draw(double deltatime) override;

    void run();

   private:
    void loadExampleScene();
};
}  // namespace daft::app