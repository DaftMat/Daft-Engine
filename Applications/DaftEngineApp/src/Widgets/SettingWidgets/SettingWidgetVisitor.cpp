//
// Created by mathis on 26/07/2020.
//
#include "SettingWidgetVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <Engine/Drawables/Object/Sphere.hpp>

void daft::app::SettingWidgetVisitor::visit(daft::engine::Object *object) {
    m_widget = new SettingWidget(nullptr, createTransformWidget(object->getTransformations()), object->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Composite *composite) {
    m_widget = new SettingWidget(nullptr, createTransformWidget(composite->getTransformations()), composite->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Sphere *sphere) {
    core::SettingManager sm;
    engine::Sphere::Type type = sphere->type();
    sm.add("Type", int(type));
    sm.add("Meridians", sphere->meridians());
    sm.add("Parallels", sphere->parallels());
    sm.add("Subdivisions", sphere->subdivisions());
    sm.add("Resolution", sphere->resolution());

    auto ds = new DrawableSettings(sm);
    ds->addComboBox("Type", {"UV", "Icosahedron", "Cube"}, core::toUType(type));
    switch (type) {
        case engine::Sphere::Type::UV:
            ds->addIntSpinBox("Meridians", 3, 9999, 1);
            ds->addIntSpinBox("Parallels", 3, 9999, 1);
            break;
        case engine::Sphere::Type::Ico:
            ds->addIntSpinBox("Subdivisions", 0, 999, 1);
            break;
        case engine::Sphere::Type::Cube:
            ds->addIntSpinBox("Resolution", 2, 9999, 1);
            break;
    }

    m_widget = new SettingWidget(ds, createTransformWidget(sphere->getTransformations()), sphere->name());
}
