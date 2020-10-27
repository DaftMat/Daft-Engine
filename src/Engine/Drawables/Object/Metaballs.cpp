//
// Created by mathis on 27/10/2020.
//
#include "Metaballs.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Metaballs::m_nrMetaballs{0};

Metaballs::Metaballs(float cubeSize, daft::engine::Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_cubeSize{cubeSize} {}

core::SettingManager Metaballs::getSettings() const {
    core::SettingManager sm;
    if (m_selectedBall == -1) {
        sm.add("Cube Size", m_cubeSize);
    } else {
        sm.add("Position", getSelectedBall().pos);
        sm.add("Radius", getSelectedBall().radius);
    }
    return sm;
}

void Metaballs::setSettings(const core::SettingManager &s) {
    if (m_selectedBall == -1) {
        setCubeSize(s.get<float>("Cube Size"));
    } else {
        m_balls[m_selectedBall].pos = s.get<glm::vec3>("Position");
        m_balls[m_selectedBall].radius = s.get<float>("Radius");
        updateNextFrame();
    }
}

void Metaballs::setCubeSize(float cs) {
    if (cs == m_cubeSize) return;
    m_cubeSize = cs;
    updateNextFrame();
}

void Metaballs::addBall(glm::vec3 p, float radius) {
    Ball ball{};
    ball.pos = p;
    ball.radius = radius;
    m_balls.push_back(ball);
    updateNextFrame();
}

Metaballs::Ball Metaballs::getSelectedBall() const {
    if (m_selectedBall >= 0) {
        return m_balls[m_selectedBall];
    }
    return Ball{};  ///< dummy ball
}

void Metaballs::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine
