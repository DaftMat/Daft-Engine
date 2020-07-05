//
// Created by mathis on 09/05/2020.
//
#pragma once

#include <vector>

#include "SettingManager.hpp"
#include "Texture.hpp"

namespace stardust::core::mat {
/**
 * surface appearance data of an object.
 */
class Material : public utils::NonCopyable {
   public:
    /**
     * default constructor.
     */
    Material() = default;

    /**
     * Move constructor.
     */
    Material(Material &&) = default;

    /**
     * Move assignment operator.
     * @return reference to this.
     */
    Material &operator=(Material &&) = default;

    /**
     * Preparation of the textures to be rendered.
     */
    void prepare() const;

    /**
     * Adds a texture to the material.
     * @param name - name of the texture.
     * @param file - path of the texture.
     */
    void addTexture(Texture texture);

    /**
     * Deletes a texture from the material.
     * @param name - name of the texture to be deleted.
     */
    void deleteTexture(const std::string &name);

    /**
     * Adds a setting to the material.
     * @tparam T - type of the setting's data.
     * @param name - name of the setting.
     * @param data - data of the setting.
     */
    template <typename T>
    void addSetting(std::string name, T data) {
        ENGINE_INFO("Setting of type {0} added to Material : {1}.", typeid(data).name(), name);
        m_settings.add(std::move(name), data);
    }

    /**
     * Sets the data of a setting in the material.
     * @tparam T - type of the setting's data
     * @param name - name of the setting to be set.
     * @param data - new data of the setting.
     */
    template <typename T>
    void setSetting(std::string name, T data) {
        m_settings.set(std::move(name), data);
    }

    /**
     * Delete a setting.
     * @tparam T - type of the setting.
     * @param name - name of the setting.
     */
    template <typename T>
    void deleteSetting(std::string name) {
        ENGINE_INFO("Setting {0} deleted from Material.", name);
        m_settings.remove<T>(std::move(name));
    }

    /**
     * Texture accessor.
     * @param name - name of the texture.
     * @return reference to the texture.
     */
    Texture &texture(const std::string &name);

    /**
     * Resetting the material makes it empty.
     */
    void reset();

    /**
     * Textures list getter.
     * @return list of textures in the material.
     */
    [[nodiscard]] const std::vector<Texture> &textures() const { return m_textures; }

    /**
     * Settings list getter.
     * @return list of settings in the material.
     */
    template <typename T>
    [[nodiscard]] const std::vector<SettingManager::Setting<T>> &settings() const {
        return m_settings.settings<T>();
    }

   private:
    std::vector<Texture> m_textures;
    SettingManager m_settings{};
};
}  // namespace stardust::core::mat