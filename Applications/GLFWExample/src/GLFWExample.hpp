//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <Core/BaseApplication.hpp>
#include <Core/Log.hpp>

#include "GLFWWindow.hpp"

class GLFWExample : public ProjName::Core::BaseApplication<GLFWWindow> {
   public:
    GLFWExample();
    ~GLFWExample() override { APP_INFO("Application closed. Closing window..."); }

    void draw(double deltatime) override;

    void run();

   private:
    void loadExampleScene();
};
