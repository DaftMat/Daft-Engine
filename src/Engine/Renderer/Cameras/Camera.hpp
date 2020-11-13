//
// Created by mathis on 28/08/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/Types.hpp>

namespace daft::engine {
/**
 * A class that represents a virtual camera.
 */
class ENGINE_API Camera {
   public:
    /**
     * struct representing a mouse.
     */
    struct Mouse {
        glm::vec2 pos;                                    ///< current position of the mouse.
        enum class Button { Left, Right, Wheel } button;  ///< button that was pressed.
    };

    /**
     * Constructor.
     * no roll as this camera won't need it.
     * @param position - position of the camera
     * @param worldUp - upward direction of the camera
     * @param yaw - horizontal rotation
     * @param pitch - vertical rotation
     */
    explicit Camera(const glm::vec3& position = {0.f, 0.f, 3.f}, const glm::vec3& worldUp = {0.f, 1.f, 0.f},
                    float yaw = -90.f, float pitch = 0.f);

    /**
     * calculates view matrix.
     * @return the view matrix of the camera.
     */
    [[nodiscard]] glm::mat4 getViewMatrix() const { return glm::lookAt(m_position, m_position + m_front, m_up); }

    /**
     * fov getter.
     * @return fov (zoom) of the camera.
     */
    [[nodiscard]] float fov() const { return m_fov; }

    /**
     * position getter.
     * @return position of the camera.
     */
    [[nodiscard]] const glm::vec3& position() const { return m_position; }

    /**
     * front getter.
     * @return the direction the camera faces.
     */
    [[nodiscard]] const glm::vec3& viewDir() const { return m_front; }

    /**
     * Apply action related to mouse scroll event.
     * Makes the distance between the camera's position and target vary.
     * @param offset - change of the scroll position.
     */
    void processMouseScroll(float offset);

    /**
     * Apply action related to mouse press event.
     * Updates mouse data.
     * @param mouse - mouse data, see Mouse .
     */
    void processMousePress(Mouse mouse);

    /**
     * Apply action related to mouse release event.
     * Updates mouse data.
     */
    void processMouseRelease() { m_mousePressed = false; }

    /**
     * Apply action related to mouse move event.
     * The action depends on the button that was pressed.
     *  Left button - the camera rotates around the target.
     *  Right button - the camera translates following its up and right vectors.
     *  Wheel button - the camera translates following its front vector.
     * @param mousePos - position of the mouse.
     */
    void processMouseMove(glm::vec2 mousePos);

    /**
     * Flips the camera.
     * Inverse the yaw and the y position.
     * Useful for reflection effects on a plane surface.
     */
    void flip();

    /**
     * Target position getter.
     * @return target.
     */
    [[nodiscard]] glm::vec3 target() const { return m_target; }

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

    float m_yaw, m_pitch, m_dist;
    float m_velocity, m_sensitivity, m_fov;

    /// mouse management
    Mouse m_mouse;
    bool m_mousePressed{false};
};
}  // namespace daft::engine
