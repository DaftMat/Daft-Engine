//
// Created by mathis on 28/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <array>

#include "AttribManager.hpp"

namespace daft::core {
class ENGINE_API MarchingCube : public NonCopyable {
   public:
    struct GridCell {
        std::array<glm::vec3, 8> p;
        std::array<float, 8> v;
    };

    explicit MarchingCube(float cubeSize = 0.1f, float isoLevel = 1.f) : m_cubeSize{cubeSize}, m_isoLevel{isoLevel} {}

    ~MarchingCube() = default;

    MarchingCube(MarchingCube &&) noexcept = default;

    MarchingCube &operator=(MarchingCube &&) noexcept = default;

    [[nodiscard]] glm::vec3 gridSize() const { return m_dimensions; }

    glm::vec3 &gridSize() { return m_dimensions; }

    [[nodiscard]] float cubeSize() const { return m_cubeSize; }

    float &cubeSize() { return m_cubeSize; }

    [[nodiscard]] float isoLevel() const { return m_isoLevel; }

    float &isoLevel() { return m_isoLevel; }

    core::AttribManager buildSurface(const std::function<float(glm::vec3)> &isoSurface);

    void polygonise(GridCell cell, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
                    std::vector<GLuint> &indices);

   private:
    [[nodiscard]] glm::vec3 vertexInterp(glm::vec3 p1, glm::vec3 p2, float v1, float v2) const;

    float m_cubeSize;
    float m_isoLevel;

    glm::vec3 m_dimensions{5.f, 5.f, 5.f};

    static int m_edgeTable[256];
    static int m_triTable[256][16];
};
}  // namespace daft::core