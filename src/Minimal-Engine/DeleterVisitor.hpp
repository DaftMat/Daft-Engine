//
// Created by mathis on 11/07/2020.
//
#pragma once

#include <API.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

class ENGINE_API DeleterVisitor : public daft::core::DrawableVisitor {
   public:
    DeleterVisitor() = default;

    DeleterVisitor(DeleterVisitor &&) = default;

    DeleterVisitor &operator=(DeleterVisitor &&) = default;

    void visit(daft::engine::Object *object) override;

    void visit(daft::engine::Composite *composite) override;
};
