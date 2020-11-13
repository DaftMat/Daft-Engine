//
// Created by mathis on 15/06/2020.
//
#pragma once

#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <string>

namespace daft::core {
/**
 * A class which holds all the non-texture settings of a Material.
 * Such as diffuse color, specular color, roughness, ...
 */
class SettingManager {
   public:
    /**
     * One non-texture material settings.
     * e.g. diffuse color, procedural textures, ...
     */
    template <typename T>
    struct Setting {
        /**
         * Base constructor.
         * Creates an empty setting with a specific name.
         * @param pname - name of the setting.
         */
        explicit Setting(std::string pname) : name(std::move(pname)) {}

        /**
         * Standard constructor.
         * @param pname - name of the setting.
         * @param pdata - data of the setting.
         */
        Setting(std::string pname, T pdata) : name(std::move(pname)), data{pdata} {}

        /**
         * Equality rvalue operator.
         * Returns true if the setting has the same name. The data isn't compared.
         * @param o - rvalue to be compared
         * @return true if this and o have the same name.
         */
        bool operator==(Setting<T> &&o) const noexcept { return name == o.name; }

        /**
         * Equality lvalue operator.
         * Returns true if the setting has the same name. The data isn't compared.
         * @param o - lvalue to be compared
         * @return true if this and o have the same name.
         */
        bool operator==(const Setting<T> &o) const noexcept { return name == o.name; }

        std::string name;  ///< name of the setting.
        T data;            ///< data of the setting.
    };

    using intSetting = Setting<int>;
    using boolSetting = Setting<bool>;
    using floatSetting = Setting<float>;
    using doubleSetting = Setting<double>;
    using vec2Setting = Setting<glm::vec2>;
    using vec3Setting = Setting<glm::vec3>;
    using vec4Setting = Setting<glm::vec4>;
    using mat2Setting = Setting<glm::mat2>;
    using mat3Setting = Setting<glm::mat3>;
    using mat4Setting = Setting<glm::mat4>;

    /**
     * Default constructor.
     */
    SettingManager() noexcept = default;

    /**
     * list of settings of type T.
     * @tparam T - type of the settings.
     * @return the list of settings that have the type T.
     */
    template <typename T>
    inline const std::vector<SettingManager::Setting<T>> &settings() const;

    /**
     * list of settings of type T.
     * @tparam T - type of the settings.
     * @return reference to the list of settings that have the type T.
     */
    template <typename T>
    inline std::vector<SettingManager::Setting<T>> &settings();

    /**
     * Adds a new setting to the corresponding list.
     * @tparam T - type of the setting.
     * @param name - name of the setting.
     * @param value - data of the setting.
     */
    template <typename T>
    inline void add(std::string name, T value) noexcept;

    /**
     * Sets a setting from the corresponding list.
     * @tparam T - type of the setting.
     * @param name - name of the setting.
     * @param value - data of the setting.
     */
    template <typename T>
    inline void set(std::string name, T value) {
        get<T>(std::move(name)) = value;
    }

    /**
     * Removes a setting from the corresponding list.
     * @tparam T - type of the setting.
     * @param name - name of the setting.
     */
    template <typename T>
    inline void remove(std::string name) {
        std::remove(getIt<T>(std::move(name)));
    }

    /**
     * Clears all the settings from all the lists.
     */
    void clear() noexcept;

    /**
     * Checks if the manager is empty.
     * @return true if the manager is empty.
     */
    [[nodiscard]] bool empty() const {
        return m_bools.empty() && m_ints.empty() && m_floats.empty() && m_doubles.empty() && m_vec2s.empty() &&
               m_vec3s.empty() && m_vec4s.empty() && m_mat2s.empty() && m_mat3s.empty() && m_mat4s.empty();
    }

    template <typename T>
    inline const T &get(std::string name) const {
        return getIt<T>(std::move(name))->data;
    }

    template <typename T>
    inline T &get(std::string name);

    bool has(const std::string &name) const;

   private:
    template <typename T>
    inline auto getIt(std::string name) const;

    template <typename T>
    inline auto getIt(std::string name);

    std::vector<intSetting> m_ints;
    std::vector<boolSetting> m_bools;
    std::vector<floatSetting> m_floats;
    std::vector<doubleSetting> m_doubles;
    std::vector<vec2Setting> m_vec2s;
    std::vector<vec3Setting> m_vec3s;
    std::vector<vec4Setting> m_vec4s;
    std::vector<mat2Setting> m_mat2s;
    std::vector<mat3Setting> m_mat3s;
    std::vector<mat4Setting> m_mat4s;
};
}  // namespace daft::core
#include <Core/Materials/SettingManager.inl>