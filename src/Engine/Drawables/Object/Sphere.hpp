//
// Created by mathis on 08/08/2020.
//
#pragma once
#include <API.hpp>

#include "Object.hpp"

namespace daft::engine {
/**
 * A primitive Object that represents a sphere.
 */
class ENGINE_API Sphere : public Object {
   public:
    /**
     * Enum that describes the type of sphere to build as a mesh.
     */
    enum class Type { UV, Ico, Cube, Fibo };

    /**
     * Standard constructor.
     * @param type - type of sphere geometry.
     * @param args - settings of the sphere's geometry (meridians/parallels, subdivisions or resolution)
     * @param parent - parent Composite .
     * @param name - name of the sphere.
     */
    explicit Sphere(Type type = Type::UV, const std::vector<int> &args = {}, Composite *parent = nullptr,
                    std::string name = "Sphere" + std::to_string(m_nrSphere++));

    /**
     * Default destructor.
     */
    ~Sphere() noexcept override = default;

    /**
     * Default move constructor.
     */
    Sphere(Sphere &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Sphere &operator=(Sphere &&) noexcept = default;

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
     * Type getter.
     * @return the type of the geometry of the sphere.
     */
    [[nodiscard]] Type type() const { return m_type; }

    /**
     * Type setter.
     * @param new type of the sphere.
     */
    void setType(Type type);

    /**
     * Meridians getter.
     * used when type is Type::UV .
     * @return meridians.
     */
    [[nodiscard]] int meridians() const { return m_meridians; }

    /**
     * Meridians setter.
     * used when type is Type::UV .
     * @param m - meridians.
     */
    void setMeridians(int m);

    /**
     * Parallels getter.
     * used when type is Type::UV .
     * @return parallels.
     */
    [[nodiscard]] int parallels() const { return m_parallels; }

    /**
     * Parallels setter.
     * used when type is Type::UV .
     * @param p - parallels.
     */
    void setParallels(int p);

    /**
     * Subdivisions getter.
     * used when type is Type::Ico .
     * @return subdivisions.
     */
    [[nodiscard]] int subdivisions() const { return m_subdivisions; }

    /**
     * Subdivisions setter.
     * used when type is Type::Ico .
     * @param s - subdivisions.
     */
    void setSubdivisions(int s);

    /**
     * Resolution getter.
     * used when type is Type::Cube .
     * @return resolution.
     */
    [[nodiscard]] int resolution() const { return m_resolution; }

    /**
     * Resolution setter.
     * used when type is Type::Cube .
     * @param r - resolution.
     */
    void setResolution(int r);

    /**
     * Points getter.
     * used when type is Type::Fibo .
     * @return number of points in the fibonacci sphere.
     */
    [[nodiscard]] int points() const { return m_nrPoints; }

    /**
     * Points setter.
     * used when type is Type::Fibo .
     * @param p - new number of points.
     */
    void setPoints(int p);

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

   protected:
    void applyUpdate() override;

   private:
    void createUVSphere();
    void createIcoSphere();
    void createIcosahedron();
    void createCubeSphere();
    void createFiboSphere();

    static std::vector<glm::vec3> fibo3D(int n);
    static std::vector<GLuint> triangulateFibo(const std::vector<glm::vec3> &points);  /// < using convex hull method.

    static glm::vec3 computeHalfVertex(const glm::vec3 &a, const glm::vec3 &b) { return glm::normalize(a + b); }
    void subdivideIcosahedron();

    Type m_type;
    float m_radius{1.0};
    int m_meridians{32}, m_parallels{16};  ///< UV sphere settings.
    int m_subdivisions{3};                 ///< Icosahedron based sphere settings.
    int m_resolution{16};                  ///< Cube based sphere settings.
    int m_nrPoints{1024};                  ///< Fibonacci sphere settings.

    static int m_nrSphere;
};
}  // namespace daft::engine