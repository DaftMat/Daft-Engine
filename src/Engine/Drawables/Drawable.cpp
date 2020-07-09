//
// Created by mathis on 07/07/2020.
//
#include "Drawable.hpp"

#include <Engine/Drawables/Composite.hpp>

namespace daft::engine::objects {

Drawable::Drawable(Composite *parent) noexcept : m_parent{parent} {}

glm::mat4 Drawable::model() const {
    glm::mat4 parentModel{1.f};
    if (getParent() != nullptr) {
        parentModel = getParent()->model();
    }
    return parentModel * calculateModel();
}

const Composite *Drawable::getParent() const { return m_parent.get(); }

void Drawable::setParent(Composite *composite) { m_parent.reset(composite); }

glm::mat4 Drawable::calculateModel() const {
    return calculateScaleMat() * calculateRotationMat() * calculateTranslationMat();
}

glm::mat4 Drawable::calculateScaleMat() const { return glm::scale(glm::mat4{1.f}, m_scale); }

glm::mat4 Drawable::calculateRotationMat() const {
    auto rotX = glm::rotate(glm::mat4{1.f}, m_rotations.x, glm::vec3{1.f, 0.f, 0.f});
    auto rotY = glm::rotate(glm::mat4{1.f}, m_rotations.y, glm::vec3{0.f, 1.f, 0.f});
    auto rotZ = glm::rotate(glm::mat4{1.f}, m_rotations.z, glm::vec3{0.f, 0.f, 1.f});
    return rotX * rotY * rotZ;
}

glm::mat4 Drawable::calculateTranslationMat() const { return glm::translate(glm::mat4{1.f}, m_position); }

}  // namespace daft::engine::objects