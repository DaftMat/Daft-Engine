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

    Sphere(Type type, const std::vector<int> &args);

    ~Sphere() noexcept override = default;

    Sphere(Sphere &&) noexcept = default;

    Sphere &operator=(Sphere &&) noexcept = default;

    [[nodiscard]] Type type() const { return m_type; }

    Type &type() { return m_type; }

    [[nodiscard]] int meridians() const { return m_meridians; }

    int &meridians() { return m_meridians; }

    [[nodiscard]] int parallels() const { return m_parallels; }

    int &parallels() { return m_parallels; }

    [[nodiscard]] int subdivisions() const { return m_subdivisions; }

    int &subdivisions() { return m_subdivisions; }

    [[nodiscard]] int resolution() const { return m_resolution; }

    int &resolution() { return m_resolution; }

    void update() override;

   private:
    void createUVSphere();
    void createIcoSphere();
    void createCubeSphere();

    Type m_type;
    int m_meridians{32}, m_parallels{16};  ///< UV sphere settings.
    int m_subdivisions{3};                 ///< Icosahedron based sphere settings.
    int m_resolution{32};                  ///< Cube based sphere settings.
};
}  // namespace daft::engine