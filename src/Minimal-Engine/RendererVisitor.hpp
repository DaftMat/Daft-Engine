//
// Created by mathis on 10/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/ShaderProgram.hpp>
#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <memory>

class ENGINE_API RendererVisitor : public daft::core::utils::DrawableVisitor {
   public:
    RendererVisitor();

    ~RendererVisitor() { m_shader.reset(); }

    RendererVisitor(RendererVisitor &&) = default;

    RendererVisitor &operator=(RendererVisitor &&) = default;

    void visit(daft::engine::objects::Object *object) override;

    void visit(daft::engine::objects::Composite *composite) override;

   private:
    std::shared_ptr<daft::core::geometry::ShaderProgram> m_shader{nullptr};
};
