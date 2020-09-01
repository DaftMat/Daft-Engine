//
// Created by mathis on 29/08/2020.
//
#include "SettingEditorVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <Engine/Drawables/Object/Sphere.hpp>

void daft::app::SettingEditorVisitor::visit(daft::engine::Object *object) { object->setTransformations(m_transforms); }

void daft::app::SettingEditorVisitor::visit(daft::engine::Sphere *sphere) {
    using namespace daft::engine;
    sphere->setTransformations(m_transforms);
    sphere->type() = Sphere::Type{m_settings.get<int>("Type")};
    switch (sphere->type()) {
        case Sphere::Type::UV:
            sphere->setMeridians(m_settings.get<int>("Meridians"));
            sphere->setParallels(m_settings.get<int>("Parallels"));
            break;
        case Sphere::Type::Ico:
            sphere->setSubdivisions(m_settings.get<int>("Subdivisions"));
            break;
        case Sphere::Type::Cube:
            sphere->setResolution(m_settings.get<int>("Resolution"));
            break;
    }
}

void daft::app::SettingEditorVisitor::visit(daft::engine::Composite *composite) {
    composite->setTransformations(m_transforms);
}
