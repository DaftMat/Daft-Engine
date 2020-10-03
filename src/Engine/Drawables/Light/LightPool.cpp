//
// Created by mathis on 11/09/2020.
//
#include "LightPool.hpp"

namespace daft::engine {
void LightPool::loadToShader(const core::ShaderProgram &shader) const {
    for (size_t i = 0; i < m_pointLights.size(); ++i) {
        m_pointLights[i]->loadToShader(shader, int(i));
    }
    shader.setInt("nrPointLights", int(m_pointLights.size()));

    for (size_t i = 0; i < m_dirLights.size(); ++i) {
        m_dirLights[i]->loadToShader(shader, int(i));
    }
    shader.setInt("nrDirLights", int(m_dirLights.size()));

    for (size_t i = 0; i < m_spotLights.size(); ++i) {
        m_spotLights[i]->loadToShader(shader, int(i));
    }
    shader.setInt("nrSpotLights", int(m_spotLights.size()));
}

void LightPool::remove(const std::string &name) {
    if (!m_pointLights.empty())
        m_pointLights.erase(
            std::find_if(m_pointLights.begin(), m_pointLights.end(), [&name](auto pl) { return pl->name() == name; }));
    if (!m_dirLights.empty())
        m_dirLights.erase(
            std::find_if(m_dirLights.begin(), m_dirLights.end(), [&name](auto dl) { return dl->name() == name; }));
    if (!m_spotLights.empty())
        m_spotLights.erase(
            std::find_if(m_spotLights.begin(), m_spotLights.end(), [&name](auto sl) { return sl->name() == name; }));
}

void LightPool::addPoint(std::shared_ptr<PointLight> pointLight) { m_pointLights.push_back(std::move(pointLight)); }

void LightPool::addDir(std::shared_ptr<DirLight> dirLight) { m_dirLights.push_back(std::move(dirLight)); }

void LightPool::addSpot(std::shared_ptr<SpotLight> spotLight) { m_spotLights.push_back(std::move(spotLight)); }
}  // namespace daft::engine