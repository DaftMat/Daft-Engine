//
// Created by mathis on 28/08/2020.
//
#include "Camera.hpp"

namespace daft::engine {
Camera::Camera(const glm::vec3 &position, const glm::vec3 &worldUp, float yaw, float pitch)
    : m_position{position},
      m_worldUp{worldUp},
      m_target{0.f},
      m_yaw{yaw},
      m_pitch{pitch},
      m_rot{0.f},
      m_velocity{5.f},
      m_sensitivity{1.f},
      m_fov{45.f} {
    m_dist = glm::length(m_position - m_target);
    updateCameraVectors();
}

void Camera::processMouseScroll(float offset) {
    m_dist -= offset * m_sensitivity;
    if (m_dist <= 0) m_dist = glm::epsilon<float>();
    glm::vec3 dir = glm::normalize(m_position - m_target);
    m_position = m_target + m_dist * dir;
}

void Camera::processMousePress(glm::vec2 mousePos) {
    m_mousePressed = true;
    m_mousePosition = mousePos;
}

void Camera::processMouseMove(glm::vec2 mousePos) {
    if (!m_mousePressed) return;
    auto mouseOffset = mousePos - m_mousePosition;
    m_mousePosition = mousePos;
    m_yaw += mouseOffset.x * m_sensitivity * 0.1f;
    m_pitch -= mouseOffset.y * m_sensitivity * 0.1f;
    if (m_pitch > 89.f) m_pitch = 89.f;
    if (m_pitch < -89.f) m_pitch = -89.f;
    updatePosition();
}

void Camera::flip() {
    m_pitch = -m_pitch;
    m_position.y = -m_position.y;
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    m_front = glm::normalize(glm::vec3{glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)),
                                       glm::sin(glm::radians(m_pitch)),
                                       glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch))});
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::updatePosition() {
    float hDist = m_dist * glm::cos(glm::radians(m_pitch));
    float vDist = m_dist * glm::sin(glm::radians(m_pitch));
    float xoffset = hDist * glm::cos(glm::radians(m_yaw));
    float zoffset = hDist * glm::sin(glm::radians(m_yaw));
    m_position = glm::vec3{m_target.x - xoffset, m_target.y - vDist, m_target.z - zoffset};
    updateCameraVectors();
}

}  // namespace daft::engine