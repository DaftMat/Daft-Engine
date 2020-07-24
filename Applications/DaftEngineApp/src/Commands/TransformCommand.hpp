//
// Created by mathis on 24/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/Utils/BaseCommand.hpp>
#include <memory>

namespace daft::app {

class ENGINE_API TransformCommand : public core::utils::BaseCommand {
   public:
    TransformCommand(core::mat::SettingManager *settings, const glm::vec3 &pos, const glm::vec3 &rot,
                     const glm::vec3 &scale);

    void execute() override;

   private:
    std::shared_ptr<core::mat::SettingManager> m_settings;
    glm::vec3 m_position;
    glm::vec3 m_rotations;
    glm::vec3 m_scale;
};
}  // namespace daft::app