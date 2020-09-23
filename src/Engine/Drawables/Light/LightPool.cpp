//
// Created by mathis on 11/09/2020.
//
#include "LightPool.hpp"

#include "PointLight.hpp"

namespace daft::engine {
void LightPool::loadToShader(const core::ShaderProgram &shader) const {
    for (size_t i = 0; i < m_pointLights.size(); ++i) {
        m_pointLights[i]->loadToShader(shader, int(i));
    }
    shader.setInt("nrPointLights", int(m_pointLights.size()));
}

void LightPool::remove(const std::string &name) {
    m_pointLights.erase(
        std::find_if(m_pointLights.begin(), m_pointLights.end(), [&name](auto pl) { return pl->name() == name; }));
    // m_dirLights.erase(std::find_if(m_dirLights.begin(), m_dirLights.end(), [&name](auto dl){ return dl->name() ==
    // name; }));
    // m_spotLights.erase(std::find_if(m_spotLights.begin(), m_spotLights.end(), [&name](auto sl){ return
    // sl->name() == name; }));
}

void LightPool::add(std::shared_ptr<PointLight> pointLight) { m_pointLights.push_back(std::move(pointLight)); }

void LightPool::add(std::shared_ptr<DirLight> dirLight) { m_dirLights.push_back(std::move(dirLight)); }

void LightPool::add(std::shared_ptr<SpotLight> spotLight) { m_spotLights.push_back(std::move(spotLight)); }
}  // namespace daft::engine