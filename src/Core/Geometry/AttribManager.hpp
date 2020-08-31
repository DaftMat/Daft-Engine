//
// Created by mathis on 22/06/2020.
//
#pragma once

#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace daft::core {
/**
 * A class that holds a list for each attributes of a Mesh
 */
class AttribManager {
   public:
    /**
     * The list wrapper for one attribute buffer.
     * @tparam T - type of the attributes.
     */
    template <typename T>
    struct AttribHandler {
        /**
         * Default constructor.
         */
        AttribHandler() = default;

        /**
         * Standard constructor.
         * @param pattribs - list of attributes.
         */
        explicit AttribHandler(std::vector<T> pattribs) noexcept : attribs{std::move_if_noexcept(pattribs)} {}

        /**
         * Stride of the attributes (i.e. size of one attribute).
         * @return stride.
         */
        [[nodiscard]] std::size_t stride() const { return sizeof(T); }

        /**
         * Return the number of elements in one element of this attrib.
         * @return data size.
         */
        [[nodiscard]] std::size_t dataSize() const { return stride() / sizeof(float); }

        /**
         * Total size of the buffer.
         * @return size.
         */
        [[nodiscard]] std::size_t size() const { return attribs.size() * stride(); }

        std::vector<T> attribs{};  ///< list of attributes
    };

   public:
    /**
     * Default constructor.
     */
    AttribManager() noexcept : m_numAttribs{0} {}

    /**
     * Adds an empty attribute buffer to the manager.
     * @tparam T - type of the attributes.
     */
    template <typename T>
    inline void addAttrib();

    /**
     * Adds an attribute buffer to the manager.
     * @tparam T - type of the attributes.
     * @param attribs - attribute buffer.
     */
    template <typename T>
    inline void addAttrib(std::vector<T> attribs);

    /**
     * get the size of the manager.
     * @return number of attrib handlers in the manager.
     */
    std::size_t size() const { return m_numAttribs; }

    /**
     * Set attrib pointers to the opengl buffer objects.
     * @param vbos - buffer objects to set the attrib pointer to.
     */
    inline void setAttribs(const std::vector<GLuint> &vbos);

    /**
     * Set indices (topology) of the mesh that will be built using this class.
     * @param indices - topology.
     */
    inline void setIndices(std::vector<GLuint> indices) { m_indices = std::move(indices); }

    /**
     * Indices constant reference.
     * @return indices const ref.
     */
    inline const std::vector<GLuint> &indices() const { return m_indices; }

    /**
     * Indices reference.
     * @return indices ref.
     */
    inline std::vector<GLuint> &indices() { return m_indices; }

    /**
     * Clears all the attrib handlers.
     */
    inline void clear() noexcept;

    /**
     * Gets the attribute buffer.
     * @tparam T - type of the attributes.
     * @param index - index of the attribute buffer.
     * @return the attribute buffer with the corresponding index.
     */
    template <typename T>
    AttribHandler<T> *getAttribs(GLuint index);

   private:
    template <typename T>
    inline void setAttrib(GLuint index, AttribHandler<T> *attrib);

    GLuint m_numAttribs;

    std::unordered_map<GLuint, AttribHandler<float>> m_floatAttribs;
    std::unordered_map<GLuint, AttribHandler<glm::vec2>> m_vec2Attribs;
    std::unordered_map<GLuint, AttribHandler<glm::vec3>> m_vec3Attribs;
    std::unordered_map<GLuint, AttribHandler<glm::vec4>> m_vec4Attribs;

    std::vector<GLuint> m_indices;
};
}  // namespace daft::core

#include "AttribManager.inl"