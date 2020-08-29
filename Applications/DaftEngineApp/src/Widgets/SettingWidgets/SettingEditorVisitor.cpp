//
// Created by mathis on 29/08/2020.
//
#include "SettingEditorVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <Engine/Drawables/Object/Sphere.hpp>

void daft::app::SettingEditorVisitor::visit(daft::engine::Object *object) { updateTransforms(object); }

void daft::app::SettingEditorVisitor::visit(daft::engine::Sphere *sphere) {
    using namespace daft::engine;
    updateTransforms(sphere);
    switch (sphere->type()) {
        case Sphere::Type::UV:
            sphere->meridians() = m_settings.get<int>("Meridians");
            sphere->parallels() = m_settings.get<int>("Parallels");
            break;
        case Sphere::Type::Ico:
            sphere->subdivisions() = m_settings.get<int>("Subdivisions");
            break;
        case Sphere::Type::Cube:
            sphere->resolution() = m_settings.get<int>("Resolution");
            break;
    }
    sphere->updateNextFrame();
}

void daft::app::SettingEditorVisitor::visit(daft::engine::Composite *composite) { updateTransforms(composite); }
