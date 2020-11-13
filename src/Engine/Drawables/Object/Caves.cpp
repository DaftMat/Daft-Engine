//
// Created by mathis on 28/10/2020.
//
#include "Caves.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Caves::m_nrCaves{0};

Caves::Caves(float cubeSize, float isoLevel, daft::engine::Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_marchingCube(cubeSize, isoLevel), m_seed{2020} {
    m_isoSurface = [&](glm::vec3 p) { return m_noise.eval(p); };
}

void Caves::renderEdges(const core::ShaderProgram &shader) {
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

core::SettingManager Caves::getSettings() const {
    core::SettingManager sm;
    sm.add("Grid Size", m_marchingCube.gridSize());
    sm.add("Cube Size", m_marchingCube.cubeSize());
    sm.add("Iso Level", m_marchingCube.isoLevel());
    sm.add("Seed", m_seed);
    sm.add("Scale", m_noise.scale());
    sm.add("Octaves", m_noise.octaves());
    sm.add("Persistence", m_noise.persistence());
    sm.add("Lacunarity", m_noise.lacunarity());
    sm.add("Offset", offset() - 1000000.f);
    return sm;
}

void Caves::setSettings(const core::SettingManager &s) {
    if (s.has("Grid Size")) setGridSize(s.get<glm::vec3>("Grid Size"));
    if (s.has("Cube Size")) setCubeSize(s.get<float>("Cube Size"));
    if (s.has("Iso Level")) setIsoLevel(s.get<float>("Iso Level"));
    if (s.has("Seed")) setSeed(s.get<int>("Seed"));
    if (s.has("Scale")) setScale(s.get<float>("Scale"));
    if (s.has("Octaves")) setOctaves(s.get<int>("Octaves"));
    if (s.has("Persistence")) setPersistence(s.get<float>("Persistence"));
    if (s.has("Lacunarity")) setLacunarity(s.get<float>("Lacunarity"));
    if (s.has("Offset")) setOffset(s.get<glm::vec3>("Offset") + 1000000.f);
}

void Caves::setGridSize(glm::vec3 cs) {
    if (m_marchingCube.gridSize() == cs) return;
    m_marchingCube.gridSize() = cs;
    updateNextFrame();
}

void Caves::setCubeSize(float cs) {
    if (cs == m_marchingCube.cubeSize()) return;
    m_marchingCube.cubeSize() = cs;
    updateNextFrame();
}

void Caves::setIsoLevel(float il) {
    if (il == m_marchingCube.isoLevel()) return;
    m_marchingCube.isoLevel() = il;
    updateNextFrame();
}

void Caves::setSeed(int s) {
    if (m_seed == s) return;
    m_seed = s;
    m_noise.perlin().setSeed(m_seed);
    updateNextFrame();
}

void Caves::setScale(float s) {
    if (m_noise.scale() == s) return;
    m_noise.scale() = s;
    updateNextFrame();
}

void Caves::setOctaves(int o) {
    if (m_noise.octaves() == o) return;
    m_noise.octaves() = o;
    updateNextFrame();
}

void Caves::setPersistence(float p) {
    if (m_noise.persistence() == p) return;
    m_noise.persistence() = p;
    updateNextFrame();
}

void Caves::setLacunarity(float l) {
    if (m_noise.lacunarity() == l) return;
    m_noise.lacunarity() = l;
    updateNextFrame();
}

void Caves::setOffset(glm::vec3 o) {
    if (offset() == o) return;
    m_noise.xOffset() = o.x;
    m_noise.yOffset() = o.y;
    m_noise.zOffset() = o.z;
    updateNextFrame();
}

void Caves::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }

void Caves::createPerlin3D() {
    m_meshObjects.clear();
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(m_marchingCube.buildSurface(m_isoSurface));
    m_meshObjects.emplace_back(std::move(meshes));
}
}  // namespace daft::engine
