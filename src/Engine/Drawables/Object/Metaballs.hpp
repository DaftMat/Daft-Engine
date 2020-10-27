//
// Created by mathis on 27/10/2020.
//
#pragma once
#include <API.hpp>
#include <array>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API Metaballs : public Object {
   public:
    struct Ball {
        glm::vec3 pos;
        float radius;
        [[nodiscard]] float eval(glm::vec3 p) const;
    };

    struct GridCell {
        std::array<glm::vec3, 8> p;
        std::array<float, 8> v;
    };

    explicit Metaballs(float cubeSize = 0.1f, float isoLevel = 1.f, Composite *parent = nullptr,
                       std::string name = "Metaballs" + std::to_string(m_nrMetaballs++));

    ~Metaballs() override = default;

    Metaballs(Metaballs &&) noexcept = default;

    Metaballs &operator=(Metaballs &&) noexcept = default;

    /**
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Gets settings as a SettingManager.
     * @return settings of the metaballs.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Sets the settings using a SettingManager.
     * @param s - updated settings.
     */
    void setSettings(const core::SettingManager &s) override;

    void setGridSize(glm::vec3 cs);

    [[nodiscard]] glm::vec3 gridSize() const { return m_dimensions; }

    void setCubeSize(float cs);

    [[nodiscard]] float cubeSize() const { return m_cubeSize; }

    void setIsoLevel(float il);

    [[nodiscard]] float isoLevel() const { return m_isoLevel; }

    /**
     * Balls getter.
     * @return the list of balls in the metaballs.
     */
    [[nodiscard]] const auto &balls() const { return m_balls; }

    /**
     * Adds a ball to the list.
     * @param p - ball to add.
     */
    void addBall(glm::vec3 p = glm::vec3{0.f}, float radius = 1.f);

    /**
     * Gets the currently selected ball.
     * @return selected ball in the list.
     */
    [[nodiscard]] Ball getSelectedBall() const;

    /**
     * Gets the currently selected ball's index.
     * @return selection as an index.
     */
    [[nodiscard]] int getSelectedIndex() const { return m_selectedBall; }

    /**
     * Updates the currently selected ball.
     * @param b - new ball's index to be selected.
     */
    void setSelectedBall(int b) { m_selectedBall = b < int(m_balls.size()) ? b : -1; }

    /**
     * Accepts a visitor.
     * @param visitor - visitor to accept.
     */
    void accept(core::DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return nothing.
     */
    [[nodiscard]] Type getType() const override { return Type::Metaballs; }

   protected:
    void applyUpdate() override { createMetaballs(); }

   private:
    void polygonise(GridCell cell, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
                    std::vector<GLuint> &indices);
    [[nodiscard]] glm::vec3 vertexInterp(glm::vec3 p1, glm::vec3 p2, float v1, float v2) const;
    void createMetaballs();

    std::vector<Ball> m_balls;
    float m_cubeSize;
    float m_isoLevel;

    glm::vec3 m_dimensions{5.f};

    int m_selectedBall{-1};

    static int m_nrMetaballs;
    static int m_edgeTable[256];
    static int m_triTable[256][16];
};
}  // namespace daft::engine