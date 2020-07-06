//
// Created by mathis on 09/05/2020.
//

#include "Material.hpp"

#include <algorithm>

namespace daft::core::mat {
void Material::prepare() const {
    for (int i = 0; i < m_textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        m_textures[i].bind();
    }
    glActiveTexture(GL_TEXTURE0);
}

void Material::addTexture(Texture texture) {
    m_textures.emplace_back(std::move(texture));
    ENGINE_INFO("Texture added to Material.");
}

void Material::deleteTexture(const std::string &name) {
    m_textures.erase(std::remove_if(m_textures.begin(), m_textures.end(),
                                    [name](const Texture &texture) { return texture.name() == name; }),
                     m_textures.end());
    ENGINE_INFO("Texture deleted from Material.");
}

Texture &Material::texture(const std::string &name) {
    return *std::find_if(m_textures.begin(), m_textures.end(),
                         [name](const Texture &texture) { return texture.name() == name; });
}

void Material::reset() {
    m_textures.clear();
    m_settings.clear();
}
}  // namespace daft::core::mat