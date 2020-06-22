//
// Created by mathis on 09/05/2020.
//
#define STB_IMAGE_IMPLEMENTATION

#include "Texture.hpp"

#include <stb/stb_image.h>

#include <Core/Utils/Log.hpp>
#include <string>

namespace stardust::core::mat {
void Texture::bind(GLenum textureType) const { glBindTexture(textureType, m_id); }

Texture::Texture(std::string name, std::string path) : m_name{std::move(name)} {
    glGenTextures(1, &m_id);

    int width, height, numChannels;
    auto filePath = std::move(path);
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);
    if (data) {
        GLenum colorFormat;
        if (numChannels == 1)
            colorFormat = GL_RED;
        else if (numChannels == 3)
            colorFormat = GL_RGB;
        else if (numChannels == 4)
            colorFormat = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        ENGINE_ERROR("Failed to load texture {0}", filePath);
    }
    m_isValid = true;
}

Texture::Texture(std::string name, const std::array<std::string, 6> &paths) : m_name{std::move(name)} {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    int width, height, numChannels;
    for (int i = 0; i < 6; ++i) {
        unsigned char *data = stbi_load(paths.at(i).c_str(), &width, &height, &numChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
            stbi_image_free(data);
        } else {
            ENGINE_ERROR("Failed to load texture {0}", paths.at(i));
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    m_isValid = true;
}

Texture::~Texture() {
    if (m_isValid) glDeleteTextures(1, &m_id);
    m_isValid = false;
}

Texture &Texture::operator=(Texture &&other) noexcept {
    m_name = std::move_if_noexcept(other.m_name);
    m_id = other.m_id;
    m_isValid = true;
    other.m_isValid = false;
    return *this;
}
}  // namespace stardust::core::mat