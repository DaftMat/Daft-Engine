//
// Created by mathis on 15/06/2020.
//
#include "SettingManager.hpp"

namespace daft::core {
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

bool SettingManager::has(const std::string &name) const {
    return getIt<int>(name) != m_ints.end() || getIt<bool>(name) != m_bools.end() ||
           getIt<float>(name) != m_floats.end() || getIt<glm::vec2>(name) != m_vec2s.end() ||
           getIt<glm::vec3>(name) != m_vec3s.end() || getIt<glm::vec4>(name) != m_vec4s.end() ||
           getIt<glm::mat2>(name) != m_mat2s.end() || getIt<glm::mat3>(name) != m_mat3s.end() ||
           getIt<glm::mat4>(name) != m_mat4s.end();
}
}  // namespace daft::core