#include <Core/Utils/Log.hpp>

namespace stardust::core::geometry {

template <typename T>
void AttribManager::addAttrib() {
    if constexpr (std::is_same_v<T, float>) {
        m_floatAttribs.insert(std::make_pair(m_numAttribs++, std::vector<float>{}));
    } else if constexpr (std::is_same_v<T, glm::vec2>) {
        m_vec2Attribs.insert(std::make_pair(m_numAttribs++, std::vector<glm::vec2>{}));
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
        m_vec3Attribs.insert(std::make_pair(m_numAttribs++, std::vector<glm::vec3>{}));
    } else if constexpr (std::is_same_v<T, glm::vec4>) {
        m_vec4Attribs.insert(std::make_pair(m_numAttribs++, std::vector<glm::vec4>{}));
    } else {
        ENGINE_WARN("Unknown attribute type. nothing has been done.");
    }
}

template <typename T>
void AttribManager::addAttrib(std::vector<T> attribs) {
    if constexpr (std::is_same_v<T, float>) {
        m_floatAttribs.insert(std::make_pair(m_numAttribs++, std::move(attribs)));
    } else if constexpr (std::is_same_v<T, glm::vec2>) {
        m_vec2Attribs.insert(std::make_pair(m_numAttribs++, std::move(attribs)));
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
        m_vec3Attribs.insert(std::make_pair(m_numAttribs++, std::move(attribs)));
    } else if constexpr (std::is_same_v<T, glm::vec4>) {
        m_vec4Attribs.insert(std::make_pair(m_numAttribs++, std::move(attribs)));
    } else {
        ENGINE_WARN("Unknown attribute type. nothing has been done.");
    }
}

template <typename T>
AttribManager::AttribHandler<T>* AttribManager::getAttribs(GLuint index) {
    if constexpr (std::is_same_v<T, float>) {
        auto it = m_floatAttribs.find(index);
        if (it != m_floatAttribs.end()) return &it->second;
    } else if constexpr (std::is_same_v<T, glm::vec2>) {
        auto it = m_vec2Attribs.find(index);
        if (it != m_vec2Attribs.end()) return &it->second;
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
        auto it = m_vec3Attribs.find(index);
        if (it != m_vec3Attribs.end()) return &it->second;
    } else if constexpr (std::is_same_v<T, glm::vec4>) {
        auto it = m_vec4Attribs.find(index);
        if (it != m_vec4Attribs.end()) return &it->second;
    }
    return nullptr;
}

void AttribManager::setAttribs(const std::vector<GLuint>& vbos) {
    for (auto i = 0ul; i < vbos.size(); ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
        // find buffer data
        if (getAttribs<float>(i) != nullptr) {
            setAttrib(i, getAttribs<float>(i));
        } else if (getAttribs<glm::vec2>(i) != nullptr) {
            setAttrib(i, getAttribs<glm::vec2>(i));
        } else if (getAttribs<glm::vec3>(i) != nullptr) {
            setAttrib(i, getAttribs<glm::vec3>(i));
        } else if (getAttribs<glm::vec4>(i) != nullptr) {
            setAttrib(i, getAttribs<glm::vec4>(i));
        }
    }
}

template <typename T>
void AttribManager::setAttrib(GLuint index, AttribManager::AttribHandler<T>* attrib) {
    glBufferData(GL_ARRAY_BUFFER, attrib->size(), attrib->attribs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, attrib->dataSize(), GL_FLOAT, GL_FALSE, attrib->stride(), (void*)nullptr);
    glEnableVertexAttribArray(index);
}

void AttribManager::clear() noexcept {
    m_floatAttribs.clear();
    m_vec2Attribs.clear();
    m_vec3Attribs.clear();
    m_vec4Attribs.clear();
}

}  // namespace stardust::core::geometry