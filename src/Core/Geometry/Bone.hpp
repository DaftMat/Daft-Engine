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
    explicit Bone(glm::vec3 startPos = glm::vec3{0.f}, glm::vec3 endPos = glm::vec3{0.f})
        : m_startPos{startPos}, m_endPos{endPos} {}

    ~Bone() = default;

    Bone(Bone &&) noexcept = default;

    Bone &operator=(Bone &&) noexcept = default;

    [[nodiscard]] glm::vec3 startPos() const { return m_startPos; }

    [[nodiscard]] glm::vec3 endPos() const { return m_endPos; }

    [[nodiscard]] glm::vec3 meanPos() const { return (m_startPos + m_endPos) / 2.f; }

    [[nodiscard]] glm::vec3 rotations() const { return m_rotations; }

    glm::vec3 &rotations() { return m_rotations; }

    [[nodiscard]] glm::mat4 modelMatrix() const;

   private:
    [[nodiscard]] glm::mat4 rotationMatrix() const;

    glm::vec3 m_startPos;
    glm::vec3 m_endPos;

    glm::vec3 m_rotations{0.f};
};
}  // namespace daft::core