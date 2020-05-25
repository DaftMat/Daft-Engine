//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <Core/BaseApplication.hpp>
#include "GLFWWindow.hpp"

class GLFWExample : public BaseApplication {
public:
    GLFWExample();
    ~GLFWExample() override = default;

    void draw(double deltatime) override;

    void run();

private:
    void loadExampleScene();
};
