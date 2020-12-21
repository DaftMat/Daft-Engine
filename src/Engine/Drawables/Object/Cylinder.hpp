//
// Created by mathis on 05/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Bone.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API Cylinder : public Object {
   public:
    /**
     * Standard constructor.
     * @param meridians - meridians of the cylinder.
     * @param parallels - parallels of the cylinder.
     * @param radius - radius of the cylinder.
     * @param parent - parent Composite .
     * @param name - name of the cylinder.
     */
    explicit Cylinder(int meridians = 64, int parallels = 8, float radius = 1.f, Composite *parent = nullptr,
                      std::string name = "Cylinder" + std::to_string(m_nrCylinder++));

    /**
     * Default destructor.
     */
    ~Cylinder() override = default;

    /**
     * Default move constructor.
     */
    Cylinder(Cylinder &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Cylinder &operator=(Cylinder &&) noexcept = default;

    void render(const core::ShaderProgram &shader) override;

    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Gets the sphere's specific settings as a SettingManager .
     * @return settings.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Settings setter using a SettingManager .
     * @param s - settings.
     */
    void setSettings(const core::SettingManager &s) override;

    /**
     * Meridians getter.
     * @return meridians.
     */
    [[nodiscard]] int meridians() const { return m_meridians; }

    /**
     * Meridians setter.
     * @param m - meridians.
     */
    void setMeridians(int m);

    /**
     * Parallels getter.
     * @return parallels.
     */
    [[nodiscard]] int parallels() const { return m_parallels; }

    /**
     * Parallels setter.
     * @param p - parallels.
     */
    void setParallels(int p);

    /**
     * Radius getter.
     * @return radius.
     */
    [[nodiscard]] float radius() const { return m_radius; }

    /**
     * Radius setter.
     * @param r - new radius.
     */
    void setRadius(float r);

    /**
     * Accepts a DrawableVisitor .
     * @param visitor - visitor to accept.
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return Drawable::Type::Sphere .
     */
    [[nodiscard]] Drawable::Type getType() const override { return Drawable::Type::Cylinder; }

   protected:
    void applyUpdate() override { createCylinder(); }

   private:
    void createBones();
    void createCylinder();
    void createWeights(glm::vec3 pos, float &w1, float &w2) const;
    void createDisk(glm::vec3 pole, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
                    std::vector<glm::vec3> &tangents, std::vector<glm::vec4> &skinWeights,
                    std::vector<glm::vec4> &skinIndices, std::vector<GLuint> &indices) const;

    int m_meridians;
    int m_parallels;
    float m_radius;

    std::vector<core::Bone> m_bones;

    static int m_nrCylinder;
};
}  // namespace daft::engine