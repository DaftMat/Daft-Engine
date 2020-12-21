//
// Created by mathis on 05/12/2020.
//
#include "Bone.hpp"

namespace daft::core {
glm::mat4 Bone::modelMatrix() const {
    glm::mat4 baseTranslation = glm::translate(glm::mat4{1.f}, m_startPos);
    return rotationMatrix();  // * glm::inverse(baseTranslation);
}

glm::mat4 Bone::rotationMatrix() const {
    glm::mat4 rot{1.f};
    rot = glm::rotate(rot, glm::radians(m_rotations.x), {1.f, 0.f, 0.f});
    rot = glm::rotate(rot, glm::radians(m_rotations.y), {0.f, 1.f, 0.f});
    rot = glm::rotate(rot, glm::radians(m_rotations.z), {0.f, 0.f, 1.f});
    return rot;
}
}  // namespace daft::core