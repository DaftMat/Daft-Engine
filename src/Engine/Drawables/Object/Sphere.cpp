//
// Created by mathis on 08/08/2020.
//
#include "Sphere.hpp"

namespace daft::engine {

Sphere::Sphere(Sphere::Type type, const std::vector<int> &args) : m_type{type} {
    if (!args.empty()) {
        switch (m_type) {
            case Type::UV:
                m_meridians = args[0];
                m_parallels = args[1];
                break;
            case Type::Ico:
                m_subdivisions = args[0];
                break;
            case Type::Cube:
                m_resolution = args[0];
                break;
        }
    }
    Sphere::update();
}

void Sphere::update() {
    switch (m_type) {
        case Type::UV:
            createUVSphere();
            break;
        case Type::Ico:
            createIcoSphere();
            break;
        case Type::Cube:
            createCubeSphere();
            break;
    }
}
}  // namespace daft::engine