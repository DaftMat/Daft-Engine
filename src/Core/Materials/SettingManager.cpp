//
// Created by mathis on 15/06/2020.
//
#include "SettingManager.hpp"

namespace daft::core::mat {
void SettingManager::clear() noexcept {
    m_ints.clear();
    m_bools.clear();
    m_floats.clear();
    m_vec2s.clear();
    m_vec3s.clear();
    m_vec4s.clear();
    m_mat2s.clear();
    m_mat3s.clear();
    m_mat4s.clear();
}
}  // namespace daft::core::mat