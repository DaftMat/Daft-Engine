//
// Created by mathis on 05/12/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <Core/Utils/Types.hpp>

namespace daft::core {
class Bone : public NonCopyable {
   public:
    explicit Bone(glm::vec3 startPos = glm::vec3{0.f}, glm::vec3 endPos = glm::vec3{0.f});

    ~Bone() = default;

    Bone(Bone &&) noexcept = default;

    Bone &operator=(Bone &&) noexcept = default;

    glm::vec3 startPos() { return m_startPos; }

    glm::vec3 endPos() { return m_endPos; }

    glm::vec3 meanPos() { return (m_startPos + m_endPos) / 2.f; }

    /**
     * Model matrix used to transform the bone's mesh.
     * @return transformation matrix of the bone's mesh.
     */
    glm::mat4 model() { return translationMatrix() * rotationMatrix(); }

    /**
     * Model matrix used to transform vertices.
     * @return transformation matrix of the bone.
     */
    glm::mat4 matrix() { return rotationMatrix(); }

   private:
    glm::mat4 translationMatrix() { return glm::translate(glm::mat4{1.f}, m_startPos); }
    glm::mat4 rotationMatrix();

    glm::vec3 m_startPos;
    glm::vec3 m_endPos;
    glm::vec3 m_rotations;
};
}  // namespace daft::core