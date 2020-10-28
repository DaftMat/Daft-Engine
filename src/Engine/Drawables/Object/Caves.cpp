//
// Created by mathis on 28/10/2020.
//
#include "Caves.hpp"

namespace daft::engine {
Caves::Caves(float cubeSize, float isoLevel, daft::engine::Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_marchingCube(cubeSize, isoLevel), m_seed{2020} {}
}  // namespace daft::engine
