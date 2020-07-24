//
// Created by mathis on 24/07/2020.
//
#include "TransformCommand.hpp"

namespace daft::app {
TransformCommand::TransformCommand(core::mat::SettingManager *settings, const glm::vec3 &pos, const glm::vec3 &rot,
                                   const glm::vec3 &scale)
    : m_settings{settings}, m_position{pos}, m_rotations{rot}, m_scale{scale} {}

void TransformCommand::execute() {
    m_settings->get<glm::vec3>("position") = m_position;
    m_settings->get<glm::vec3>("rotations") = m_rotations;
    m_settings->get<glm::vec3>("scale") = m_scale;
}
}  // namespace daft::app