#include <Core/Utils/Logger.hpp>

#include "SettingManager.hpp"

namespace daft::core::mat {
template <typename T>
const std::vector<SettingManager::Setting<T>>& SettingManager::settings() const {
    if constexpr (std::is_same_v<T, int>)
        return m_ints;
    else if constexpr (std::is_same_v<T, bool>)
        return m_bools;
    else if constexpr (std::is_same_v<T, float>)
        return m_floats;
    else if constexpr (std::is_same_v<T, glm::vec2>)
        return m_vec2s;
    else if constexpr (std::is_same_v<T, glm::vec3>)
        return m_vec3s;
    else if constexpr (std::is_same_v<T, glm::vec4>)
        return m_vec4s;
    else if constexpr (std::is_same_v<T, glm::mat2>)
        return m_mat2s;
    else if constexpr (std::is_same_v<T, glm::mat3>)
        return m_mat3s;
    else if constexpr (std::is_same_v<T, glm::mat4>)
        return m_mat4s;
    core::utils::Logger::info() << "invalid setting type, returning empty list...\n";
    return std::vector<Setting<T>>{};
}

template <typename T>
std::vector<SettingManager::Setting<T>>& SettingManager::settings() {
    return const_cast<std::vector<Setting<T>>&>(static_cast<const SettingManager&>(*this).settings<T>());
}

template <typename T>
void SettingManager::add(std::string name, T value) noexcept {
    if constexpr (std::is_same_v<T, int>)
        m_ints.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, bool>)
        m_bools.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, float>)
        m_floats.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, glm::vec2>)
        m_vec2s.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, glm::vec3>)
        m_vec3s.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, glm::vec4>)
        m_vec4s.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, glm::mat2>)
        m_mat2s.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, glm::mat3>)
        m_mat3s.emplace_back(std::move_if_noexcept(name), value);
    else if constexpr (std::is_same_v<T, glm::mat4>)
        m_mat4s.emplace_back(std::move_if_noexcept(name), value);
    else {
        core::utils::Logger::info() << "invalid setting type, nothing has been done.\n";
    }
}

template <typename T>
auto SettingManager::getIt(std::string name) const {
    return std::find(settings<T>().begin(), settings<T>().end(), Setting<T>(std::move(name)));
}

template <typename T>
auto SettingManager::getIt(std::string name) {
    std::string iname = std::move(name);
    return const_cast<decltype(getIt<T>(iname))&>(static_cast<const SettingManager&>(*this).getIt<T>(iname));
}

template <typename T>
T& SettingManager::get(std::string name) {
    return const_cast<T&>(static_cast<const SettingManager&>(*this).get<T>(std::move(name)));
}

bool SettingManager::empty() noexcept {
    return m_bools.empty() && m_ints.empty() && m_floats.empty() && m_vec2s.empty() && m_vec3s.empty() &&
           m_vec4s.empty() && m_mat2s.empty() && m_mat3s.empty() && m_mat4s.empty();
}
}  // namespace daft::core::mat