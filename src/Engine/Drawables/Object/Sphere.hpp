//
// Created by mathis on 08/08/2020.
//
#pragma once
#include <API.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API Sphere : public Object {
   public:
    enum class Type { UV, Ico, Cube };

    explicit Sphere(Type type = Type::UV, const std::vector<int> &args = {}, Composite *parent = nullptr,
                    std::string name = "Sphere" + std::to_string(m_nrSphere++));

    ~Sphere() noexcept override = default;

    Sphere(Sphere &&) noexcept = default;

    Sphere &operator=(Sphere &&) noexcept = default;

    [[nodiscard]] Type type() const { return m_type; }

    Type &type() { return m_type; }

    [[nodiscard]] int meridians() const { return m_meridians; }

    void setMeridians(int m);

    [[nodiscard]] int parallels() const { return m_parallels; }

    void setParallels(int p);

    [[nodiscard]] int subdivisions() const { return m_subdivisions; }

    void setSubdivisions(int s);

    [[nodiscard]] int resolution() const { return m_resolution; }

    void setResolution(int r);

    void accept(DrawableVisitor *visitor) override;

    // void update() override {
    //    if (m_update) {
    //        applyUpdate();
    //    }
    //}

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