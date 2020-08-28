//
// Created by mathis on 10/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/ShaderProgram.hpp>
#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <memory>

class ENGINE_API RendererVisitor : public daft::core::DrawableVisitor {
   public:
    RendererVisitor();

    ~RendererVisitor() { m_shader.reset(); }

    RendererVisitor(RendererVisitor &&) = default;

    RendererVisitor &operator=(RendererVisitor &&) = default;

    void visit(daft::engine::Object *object) override { render(object); }

    void visit(daft::engine::Sphere *sphere) override { render(sphere); }

    void visit(daft::engine::Composite *composite) override;

   private:
    template <typename T>
    void render(T drawable);

    std::shared_ptr<daft::core::ShaderProgram> m_shader{nullptr};
};
