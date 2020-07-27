//
// Created by mathis on 11/07/2020.
//
#include "DeleterVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/Object.hpp>

void DeleterVisitor::visit(daft::engine::objects::Object *object) { object->reset(); }

void DeleterVisitor::visit(daft::engine::objects::Composite *composite) {
    DrawableVisitor::visit(composite);
    composite->reset();
}
