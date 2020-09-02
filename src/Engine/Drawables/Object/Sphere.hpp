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
    enum class Type { UV, Ico, Cube };

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
     * Type getter.
     * @return the type of the geometry of the sphere.
     */
    [[nodiscard]] Type type() const { return m_type; }

    /**
     * Type reference getter.
     * @return ref to the type of the geometry of the sphere.
     */
    Type &type() { return m_type; }

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

    Type m_type;
    int m_meridians{32}, m_parallels{16};  ///< UV sphere settings.
    int m_subdivisions{3};                 ///< Icosahedron based sphere settings.
    int m_resolution{32};                  ///< Cube based sphere settings.

    static int m_nrSphere;
};
}  // namespace daft::engine