//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <memory>
#include <Minimal-Engine/Renderer.hpp>

class BaseApplication {
public:
    BaseApplication() = default;
    virtual ~BaseApplication() { m_renderer.reset(); Loader::clean(); }

    virtual void draw(double deltatime) = 0;

protected:
    std::unique_ptr<Renderer> m_renderer;

    void init(int width, int height) { m_renderer = std::make_unique<Renderer>(width, height); }
};