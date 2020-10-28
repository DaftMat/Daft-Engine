//
// Created by mathis on 27/10/2020.
//
#include "Metaballs.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Metaballs::m_nrMetaballs{0};

Metaballs::Metaballs(float cubeSize, float isoLevel, daft::engine::Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_marchingCube{cubeSize, isoLevel} {
    m_isoSurface = [&](glm::vec3 p) {
        float v = 0.f;
        for (auto &ball : m_balls) v += ball.eval(p);
        return v;
    };
}

void Metaballs::renderEdges(const core::ShaderProgram &shader) {
    Object::renderEdges(shader);

    auto gs = m_marchingCube.gridSize();
    std::vector<glm::vec3> positions{
        -gs, {gs.x, -gs.y, -gs.z}, {gs.x, -gs.y, gs.z}, {-gs.x, -gs.y, gs.z}, {-gs.x, gs.y, -gs.z}, {gs.x, gs.y, -gs.z},
        gs,  {-gs.x, gs.y, gs.z}};
    std::vector<GLuint> indices{0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7};

    core::AttribManager am;
    am.addAttrib(positions);
    am.indices() = indices;

    core::Mesh mesh{am};

    if (selected())
        shader.setVec3("color", {1.f, 1.f, 0.f});
    else
        shader.setVec3("color", glm::vec3{1.f});
    mesh.prepare();
    mesh.render(GL_LINES);
    mesh.unbind();
    shader.setVec3("color", glm::vec3{0.f});
}

core::SettingManager Metaballs::getSettings() const {
    core::SettingManager sm;
    if (m_selectedBall == -1) {
        sm.add("Grid Size", m_marchingCube.gridSize());
        sm.add("Cube Size", m_marchingCube.cubeSize());
        sm.add("Iso Level", m_marchingCube.isoLevel());
    } else {
        sm.add("Position", getSelectedBall().pos);
        sm.add("Radius", getSelectedBall().radius);
    }
    return sm;
}

void Metaballs::setSettings(const core::SettingManager &s) {
    if (m_selectedBall == -1) {
        setGridSize(s.get<glm::vec3>("Grid Size"));
        setCubeSize(s.get<float>("Cube Size"));
        setIsoLevel(s.get<float>("Iso Level"));
    } else {
        m_balls[m_selectedBall].pos = s.get<glm::vec3>("Position");
        m_balls[m_selectedBall].radius = s.get<float>("Radius");
        updateNextFrame();
    }
}

void Metaballs::setGridSize(glm::vec3 cs) {
    if (cs == m_marchingCube.gridSize()) return;
    m_marchingCube.gridSize() = cs;
    updateNextFrame();
}

void Metaballs::setCubeSize(float cs) {
    if (cs == m_marchingCube.cubeSize()) return;
    m_marchingCube.cubeSize() = cs;
    updateNextFrame();
}

void Metaballs::setIsoLevel(float il) {
    if (il == m_marchingCube.isoLevel()) return;
    m_marchingCube.isoLevel() = il;
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

float Metaballs::Ball::eval(glm::vec3 p) const {
    glm::vec3 s = p - pos;
    return (radius * radius) / (s.x * s.x + s.y * s.y + s.z * s.z);
}

void Metaballs::createMetaballs() {
    m_meshObjects.clear();
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(m_marchingCube.buildSurface(m_isoSurface));
    m_meshObjects.emplace_back(std::move(meshes));
}

}  // namespace daft::engine
