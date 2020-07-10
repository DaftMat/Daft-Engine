//
// Created by mathis on 11/07/2020.
//
#pragma once

#include <API.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

class ENGINE_API DeleterVisitor : public daft::core::utils::DrawableVisitor {
   public:
    DeleterVisitor() = default;

    DeleterVisitor(DeleterVisitor &&) = default;

    DeleterVisitor &operator=(DeleterVisitor &&) = default;

    void visit(daft::engine::objects::Object *object) const override;

    void visit(daft::engine::objects::Composite *composite) const override;
};
