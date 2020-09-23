//
// Created by mathis on 26/07/2020.
//
#include "SettingWidgetVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/primitives.hpp>

void daft::app::SettingWidgetVisitor::visit(daft::engine::Object *object) {
    m_widget = new SettingWidget(nullptr, createTransformWidget(object->getTransformations()), object->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Composite *composite) {
    m_widget = new SettingWidget(nullptr, createTransformWidget(composite->getTransformations()), composite->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Sphere *sphere) {
    core::SettingManager sm = sphere->getSettings();
    engine::Sphere::Type type = sphere->type();

    auto ds = new DrawableSettings(sm);
    ds->addComboBox("Type", {"UV", "Icosahedron", "Cube", "Fibonacci"}, core::toUType(type));
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
        case engine::Sphere::Type::Fibo:
            ds->addIntSpinBox("Points", 8, 999999, 10);
            break;
    }
    ds->addDoubleSpinBox("Radius", 0, 9999, 0.1);

    m_widget = new SettingWidget(ds, createTransformWidget(sphere->getTransformations()), sphere->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Torus *torus) {
    core::SettingManager sm = torus->getSettings();
    auto ds = new DrawableSettings(sm);
    ds->addIntSpinBox("Meridians", 3, 9999, 1);
    ds->addIntSpinBox("Parallels", 3, 9999, 1);
    ds->addDoubleSpinBox("Inner Radius", 0, 9999, 0.1);
    ds->addDoubleSpinBox("Outer Radius", 0, 9999, 0.1);
    m_widget = new SettingWidget(ds, createTransformWidget(torus->getTransformations()), torus->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Cube *cube) {
    core::SettingManager sm = cube->getSettings();
    auto ds = new DrawableSettings(sm);
    ds->addIntSpinBox("Resolution", 2, 9999, 1);
    ds->addDoubleSpinBox("Radius", 0, 9999, 0.1);
    m_widget = new SettingWidget(ds, createTransformWidget(cube->getTransformations()), cube->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::BSpline *bspline) {
    core::SettingManager sm = bspline->getSettings();
    auto ds = new DrawableSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(bspline->getTransformations()), bspline->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::PointLight *pointLight) {
    core::SettingManager sm = pointLight->getSettings();
    auto ds = new DrawableSettings(sm);
    ds->addIntSpinBoxVector("Color", 0, 255, 1, 255.f);
    ds->addDoubleSpinBox("Intensity", 0, 9999);
    m_widget = new SettingWidget(ds, createTransformWidget(pointLight->getTransformations(), true, false, false),
                                 pointLight->name());
}
