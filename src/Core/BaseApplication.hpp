//
// Created by mathis on 24/05/2020.
//
#pragma once
#include <API.hpp>

#include <memory>
#include <Minimal-Engine/Renderer.hpp>

///TODO: if you changed ENGINE_API macro, make sure you update it here.
class ENGINE_API BaseApplication {
public:
    BaseApplication() = default;
    virtual ~BaseApplication() { m_renderer.reset(); Loader::clean(); }

    virtual void draw(double deltatime) = 0;

protected:
    std::unique_ptr<Renderer> m_renderer;

    void init(int width, int height) { m_renderer = std::make_unique<Renderer>(width, height); }
};