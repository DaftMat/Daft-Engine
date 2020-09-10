//
// Created by mathis on 10/09/2020.
//
#include "Torus.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Torus::m_nrTorus{0};

Torus::Torus(int meridians, int parallels, float innerRadius, float outerRadius, Composite *parent, std::string name)
    : Object(parent, std::move(name), {}),
      m_meridians{meridians},
      m_parallels{parallels},
      m_innerRadius{innerRadius},
      m_outerRadius{outerRadius} {
    createTorus();
}

core::SettingManager Torus::getSettings() const {
    core::SettingManager sm;
    sm.add("Meridians", m_meridians);
    sm.add("Parallels", m_parallels);
    sm.add("Inner Radius", m_innerRadius);
    sm.add("Outer Radius", m_outerRadius);
    return sm;
}

void Torus::setSettings(const core::SettingManager &s) {
    setMeridians(s.get<int>("Meridians"));
    setParallels(s.get<int>("Parallels"));
    setInnerRadius(s.get<float>("Inner Radius"));
    setOuterRadius(s.get<float>("Outer Radius"));
}

void Torus::setMeridians(int m) {
    if (m_meridians == m) return;
    m_meridians = m;
    updateNextFrame();
}

void Torus::setParallels(int p) {
    if (m_parallels == p) return;
    m_parallels = p;
    updateNextFrame();
}

void Torus::setInnerRadius(float r) {
    if (m_innerRadius == r) return;
    m_innerRadius = r;
    updateNextFrame();
}

void Torus::setOuterRadius(float r) {
    if (m_outerRadius == r) return;
    m_outerRadius = r;
    updateNextFrame();
}

void Torus::createTorus() {}

void Torus::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine