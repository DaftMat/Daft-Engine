//
// Created by mathis on 11/07/2020.
//
#include "DeleterVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <Engine/Drawables/Object/Sphere.hpp>

void DeleterVisitor::visit(daft::engine::Object *object) { object->reset(); }

void DeleterVisitor::visit(daft::engine::Sphere *sphere) { sphere->reset(); }

void DeleterVisitor::visit(daft::engine::Composite *composite) {
    DrawableVisitor::visit(composite);
    composite->reset();
}
