//
// Created by mathis on 07/07/2020.
//
#include "Drawable.hpp"

#include <Engine/Drawables/Composite.hpp>

namespace daft::engine::objects {

int Drawable::m_nrDrawables{0};

Drawable::Drawable(Composite *parent, std::string name) noexcept
    : m_parent{parent}, m_name{std::move_if_noexcept(name)} {}

glm::mat4 Drawable::model() const {
    glm::mat4 parentModel{1.f};
    if (getParent() != nullptr) {
        parentModel = getParent()->model();
    }
    return parentModel * calculateModel();
}

glm::mat4 Drawable::normalizedModel() const {
    glm::mat4 parentModel{1.f};
    if (getParent() != nullptr) {
        parentModel = getParent()->normalizedModel();
    }
    return parentModel * calculateNormalizedModel();
}

const Composite *Drawable::getParent() const { return m_parent; }

void Drawable::setParent(Composite *composite) { m_parent = composite; }

glm::mat4 Drawable::calculateModel() const { return calculateNormalizedModel() * calculateTranslationMat(); }

glm::mat4 Drawable::calculateNormalizedModel() const { return calculateScaleMat() * calculateRotationMat(); }

glm::mat4 Drawable::calculateScaleMat() const { return glm::scale(glm::mat4{1.f}, m_scale); }

glm::mat4 Drawable::calculateRotationMat() const {
    auto rotX = glm::rotate(glm::mat4{1.f}, m_rotations.x, glm::vec3{1.f, 0.f, 0.f});
    auto rotY = glm::rotate(glm::mat4{1.f}, m_rotations.y, glm::vec3{0.f, 1.f, 0.f});
    auto rotZ = glm::rotate(glm::mat4{1.f}, m_rotations.z, glm::vec3{0.f, 0.f, 1.f});
    return rotX * rotY * rotZ;
}

glm::mat4 Drawable::calculateTranslationMat() const { return glm::translate(glm::mat4{1.f}, m_position); }

}  // namespace daft::engine::objects