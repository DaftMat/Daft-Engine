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
    /**
     * Represents a cube sample.
     */
    struct GridCell {
        std::array<glm::vec3, 8> p;  /// position of the cube
        std::array<float, 8> v;      /// iso values of each cube's point
    };

    /**
     * Standard constructor.
     * @param cubeSize - size of a sample (smaller = more detailed mesh).
     * @param isoLevel - iso value that represent the surface.
     */
    explicit MarchingCube(float cubeSize = 0.1f, float isoLevel = 1.f) : m_cubeSize{cubeSize}, m_isoLevel{isoLevel} {}

    /**
     * Default destructor.
     */
    ~MarchingCube() = default;

    /**
     * Default move constructor.
     */
    MarchingCube(MarchingCube &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    MarchingCube &operator=(MarchingCube &&) noexcept = default;

    /**
     * Grid size getter.
     * @return dimensions of the sampled space.
     */
    [[nodiscard]] glm::vec3 gridSize() const { return m_dimensions; }

    /**
     * Gris size ref getter.
     * @return dimensions of the sampled space.
     */
    glm::vec3 &gridSize() { return m_dimensions; }

    /**
     * Cube size getter.
     * @return size of a cube sample.
     */
    [[nodiscard]] float cubeSize() const { return m_cubeSize; }

    /**
     * Cube size ref getter.
     * @return size of a cube sample.
     */
    float &cubeSize() { return m_cubeSize; }

    /**
     * Iso Level getter.
     * @return iso level that triggers the surface.
     */
    [[nodiscard]] float isoLevel() const { return m_isoLevel; }

    /**
     * Iso Level ref getter.
     * @return iso level that triggers the surface.
     */
    float &isoLevel() { return m_isoLevel; }

    /**
     * Builds the mesh corresponding to the iso-surface given the function of that iso-surface.
     * @param isoSurface - function to sample
     * @return AttribManager that can be passed to Mesh constructor.
     */
    core::AttribManager buildSurface(const std::function<float(glm::vec3)> &isoSurface);

    /**
     * Runs one cube sample in the sampled space.
     * @param cell - sample.
     * @param positions - mesh data to update.
     * @param normals - mesh data to update.
     * @param indices - mesh data to update.
     */
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