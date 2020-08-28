//
// Created by mathis on 28/08/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/Types.hpp>

namespace daft::engine {
class ENGINE_API Camera {
   public:
    /** Constructor.
     * no roll as this camera won't need it.
     * @param position - position of the camera
     * @param worldUp - upward direction of the camera
     * @param yaw - horizontal rotation
     * @param pitch - vertical rotation
     */
    explicit Camera(const glm::vec3& position = {0.f, 0.f, -3.f}, const glm::vec3& worldUp = {0.f, 1.f, 0.f},
                    float yaw = 90.f, float pitch = 0.f);

    /** calculates view matrix.
     *
     * @return the view matrix of the camera.
     */
    [[nodiscard]] glm::mat4 getViewMatrix() const { return glm::lookAt(m_position, m_position + m_front, m_up); }

    /** fov getter.
     *
     * @return fov (zoom) of the camera.
     */
    [[nodiscard]] float fov() const { return m_fov; }

    /** position getter.
     *
     * @return position of the camera.
     */
    [[nodiscard]] const glm::vec3& position() const { return m_position; }

    /** front getter.
     *
     * @return the direction the camera faces.
     */
    [[nodiscard]] const glm::vec3& viewDir() const { return m_front; }

    void processMouseScroll(float offset);

    void processMousePress(glm::vec2 mousePos);

    void processMouseRelease() { m_mousePressed = false; }

    void processMouseMove(glm::vec2 mousePos);

    void flip();

   private:
    void updateCameraVectors();
    void updatePosition();

    /// camera's settings
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    glm::vec3 m_target;

    float m_yaw, m_pitch, m_rot, m_dist;
    float m_velocity, m_sensitivity, m_fov;

    /// mouse management
    glm::vec2 m_mousePosition;
    bool m_mousePressed{false};
};
}  // namespace daft::engine
