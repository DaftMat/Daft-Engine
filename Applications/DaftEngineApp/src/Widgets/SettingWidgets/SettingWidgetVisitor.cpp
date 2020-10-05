//
// Created by mathis on 26/07/2020.
//
#include "SettingWidgetVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/primitiveIncludes.hpp>
#include <Widgets/SettingWidgets/DrawableSettings/BSplineSettings.hpp>
#include <Widgets/SettingWidgets/DrawableSettings/CubeSettings.hpp>
#include <Widgets/SettingWidgets/DrawableSettings/PointLightSettings.hpp>
#include <Widgets/SettingWidgets/DrawableSettings/SphereSettings.hpp>
#include <Widgets/SettingWidgets/DrawableSettings/TorusSettings.hpp>
#include <src/Widgets/SettingWidgets/DrawableSettings/CylinderSettings.hpp>
#include <src/Widgets/SettingWidgets/DrawableSettings/DirLightSettings.hpp>
#include <src/Widgets/SettingWidgets/DrawableSettings/SpotLightSettings.hpp>

void daft::app::SettingWidgetVisitor::visit(daft::engine::Object *object) {
    m_widget = new SettingWidget(nullptr, createTransformWidget(object->getTransformations()), object->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Composite *composite) {
    m_widget = new SettingWidget(nullptr, createTransformWidget(composite->getTransformations()), composite->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Sphere *sphere) {
    core::SettingManager sm = sphere->getSettings();
    DrawableSettings *ds = new SphereSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(sphere->getTransformations()), sphere->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Torus *torus) {
    core::SettingManager sm = torus->getSettings();
    DrawableSettings *ds = new TorusSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(torus->getTransformations()), torus->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Cube *cube) {
    core::SettingManager sm = cube->getSettings();
    DrawableSettings *ds = new CubeSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(cube->getTransformations()), cube->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::BSpline *bspline) {
    core::SettingManager sm = bspline->getSettings();
    DrawableSettings *ds = new BSplineSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(bspline->getTransformations()), bspline->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::Cylinder *cylinder) {
    core::SettingManager sm = cylinder->getSettings();
    DrawableSettings *ds = new CylinderSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(cylinder->getTransformations()), cylinder->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::PointLight *pointLight) {
    core::SettingManager sm = pointLight->getSettings();
    DrawableSettings *ds = new PointLightSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(pointLight->getTransformations(), true, false, false),
                                 pointLight->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::SpotLight *spotLight) {
    core::SettingManager sm = spotLight->getSettings();
    DrawableSettings *ds = new SpotLightSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(spotLight->getTransformations(), true, true, false),
                                 spotLight->name());
}

void daft::app::SettingWidgetVisitor::visit(daft::engine::DirLight *dirLight) {
    core::SettingManager sm = dirLight->getSettings();
    DrawableSettings *ds = new DirLightSettings(sm);
    m_widget = new SettingWidget(ds, createTransformWidget(dirLight->getTransformations(), false, true, false),
                                 dirLight->name());
}
