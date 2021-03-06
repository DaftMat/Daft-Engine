//
// Created by mathis on 09/05/2020.
//

#include "Material.hpp"

#include <Core/Rendering/ShaderProgram.hpp>
#include <Core/Utils/Logger.hpp>
#include <algorithm>

namespace daft::core {
Material::Material(bool isObjectMaterial) {
    if (isObjectMaterial) {
        addSetting("nrAlbedoTex", int(0));
        addSetting("nrSpecularTex", int(0));
        addSetting("nrNormalTex", int(0));
        addSetting("nrReflectionTex", int(0));
        addSetting("nrRoughnessTex", int(0));
        addSetting("nrMetalnessTex", int(0));
        addSetting("albedo", glm::vec3{0.3f});
        addSetting("specular", glm::vec3{1.f});
        addSetting("shininess", 10.f);
        addSetting("reflectivity", 1.f);
        addSetting("roughness", 0.1f);
        addSetting("metalness", 0.1f);
        addSetting("isLight", false);
    }
}

void Material::prepare() const {
    for (size_t i = 0; i < m_textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        m_textures[i].bind();
    }
    glActiveTexture(GL_TEXTURE0);
}

void Material::addTexture(Texture texture) {
    m_textures.push_back(std::move(texture));
    std::stringstream ss;
    ss << "Texture added to Material.";
    core::Logger::info(std::move(ss));
}

void Material::deleteTexture(const std::string &name) {
    m_textures.erase(std::remove_if(m_textures.begin(), m_textures.end(),
                                    [name](const Texture &texture) { return texture.name() == name; }),
                     m_textures.end());
    std::stringstream ss;
    ss << "Texture deleted from Material.";
    core::Logger::info(std::move(ss));
}

Texture &Material::texture(const std::string &name) {
    return *std::find_if(m_textures.begin(), m_textures.end(),
                         [name](const Texture &texture) { return texture.name() == name; });
}

void Material::reset() {
    m_textures.clear();
    m_settings.clear();
}

void Material::loadToShader(const ShaderProgram &shader, const std::string &name) const {
    std::string actualName = name.empty() ? "" : name + ".";
    /// Textures
    for (size_t i = 0; i < textures().size(); ++i) {
        shader.setInt(actualName + textures()[i].name(), i);
    }
    /// Int settings
    for (auto &setting : settings<int>()) {
        shader.setInt(actualName + setting.name, setting.data);
    }
    /// Bool settings
    for (auto &setting : settings<bool>()) {
        shader.setBool(actualName + setting.name, setting.data);
    }
    /// Float settings
    for (auto &setting : settings<float>()) {
        shader.setFloat(actualName + setting.name, setting.data);
    }
    /// Vec2 settings
    for (auto &setting : settings<glm::vec2>()) {
        shader.setVec2(actualName + setting.name, setting.data);
    }
    /// Vec3 settings
    for (auto &setting : settings<glm::vec3>()) {
        shader.setVec3(actualName + setting.name, setting.data);
    }
    /// Vec4 settings
    for (auto &setting : settings<glm::vec4>()) {
        shader.setVec4(actualName + setting.name, setting.data);
    }
    /// Mat2 settings
    for (auto &setting : settings<glm::mat2>()) {
        shader.setMat2(actualName + setting.name, setting.data);
    }
    /// Mat3 settings
    for (auto &setting : settings<glm::mat3>()) {
        shader.setMat3(actualName + setting.name, setting.data);
    }
    /// Mat4 settings
    for (auto &setting : settings<glm::mat4>()) {
        shader.setMat4(actualName + setting.name, setting.data);
    }
}
}  // namespace daft::core