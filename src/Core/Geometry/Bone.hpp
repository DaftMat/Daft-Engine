//
// Created by mathis on 05/12/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <Core/Utils/Types.hpp>

namespace daft::core {
/**
 * Represents an articulation.
 */
class Bone : public NonCopyable {
   public:
    /**
     * Constructor.
     * @param startPos - starting position of the bone.
     * @param endPos - ending position of the bone.
     */
    explicit Bone(glm::vec3 startPos = glm::vec3{0.f}, glm::vec3 endPos = glm::vec3{0.f})
        : m_startPos{startPos}, m_endPos{endPos} {}

    /**
     * Destructor.
     */
    ~Bone() = default;

    /**
     * Move constructor.
     */
    Bone(Bone &&) noexcept = default;

    /**
     * Move assignment operator.
     * @return ref to this.
     */
    Bone &operator=(Bone &&) noexcept = default;

    /**
     * Starting position getter.
     * @return Starting position of the bone.
     */
    [[nodiscard]] glm::vec3 startPos() const { return m_startPos; }

    /**
     * Ending position getter.
     * @return Ending position of the bone.
     */
    [[nodiscard]] glm::vec3 endPos() const { return m_endPos; }

    /**
     * Mean position getter.
     * @return The position of the center of the bone.
     */
    [[nodiscard]] glm::vec3 meanPos() const { return (m_startPos + m_endPos) / 2.f; }

    /**
     * Rotations getter.
     * The vector represents the rotation angle around each of the 3 axis X, Y, Z.
     * @return a vector of rotations.
     */
    [[nodiscard]] glm::vec3 rotations() const { return m_rotations; }

    /**
     * Rotations reference getter.
     * @return ref to vector of rotations.
     */
    glm::vec3 &rotations() { return m_rotations; }

    /**
     * Calculates the transformation matrix of the bone.
     * @return model matrix of the bone.
     */
    [[nodiscard]] glm::mat4 modelMatrix() const;

   private:
    [[nodiscard]] glm::mat4 rotationMatrix() const;

    glm::vec3 m_startPos;
    glm::vec3 m_endPos;

    glm::vec3 m_rotations{0.f};
};
}  // namespace daft::core