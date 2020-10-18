//
// Created by mathis on 11/09/2020.
//
#include "LightPool.hpp"

namespace daft::engine {
void LightPool::loadToShader(const core::ShaderProgram &shader) const {
    int index = 0;
    for (size_t i = 0; i < m_pointLights.size(); ++i) {
        m_pointLights[i]->loadToShader(shader, int(i));
        shader.setInt("pointLights[" + std::to_string(i) + "].shadowData.shadowMap", 31 - index);
        glActiveTexture(GL_TEXTURE31 - index++);
        m_pointLights[i]->shadowMap().bind();
    }
    shader.setInt("nrPointLights", int(m_pointLights.size()));

    for (size_t i = 0; i < m_dirLights.size(); ++i) {
        m_dirLights[i]->loadToShader(shader, int(i));
        shader.setInt("dirLights[" + std::to_string(i) + "].shadowData.shadowMap", 31 - index);
        glActiveTexture(GL_TEXTURE31 - index++);
        m_dirLights[i]->shadowMap().bind();
    }
    shader.setInt("nrDirLights", int(m_dirLights.size()));

    for (size_t i = 0; i < m_spotLights.size(); ++i) {
        m_spotLights[i]->loadToShader(shader, int(i));
        shader.setInt("spotLights[" + std::to_string(i) + "].shadowData.shadowMap", 31 - index);
        glActiveTexture(GL_TEXTURE31 - index++);
        m_spotLights[i]->shadowMap().bind();
    }
    shader.setInt("nrSpotLights", int(m_spotLights.size()));
}

void LightPool::renderToLightMap(Composite *root, const core::ShaderProgram &shader, int screenWidth, int screenHeight,
                                 const Camera &viewCam) {
    for (auto &pointLight : m_pointLights) {
        pointLight->renderToLightMap(root, shader, screenWidth, screenHeight, viewCam);
    }
    for (auto &dirLight : m_dirLights) {
        dirLight->renderToLightMap(root, shader, screenWidth, screenHeight, viewCam);
    }
    for (auto &spotLight : m_spotLights) {
        spotLight->renderToLightMap(root, shader, screenWidth, screenHeight, viewCam);
    }
}

void LightPool::remove(const std::string &name) {
    for (size_t i = 0; i < m_pointLights.size(); ++i) {
        if (m_pointLights[i]->name() == name) {
            m_pointLights.erase(m_pointLights.begin() + i);
        }
    }
    for (size_t i = 0; i < m_dirLights.size(); ++i) {
        if (m_dirLights[i]->name() == name) {
            m_dirLights.erase(m_dirLights.begin() + i);
        }
    }
    for (size_t i = 0; i < m_spotLights.size(); ++i) {
        if (m_spotLights[i]->name() == name) {
            m_spotLights.erase(m_spotLights.begin() + i);
        }
    }
}

void LightPool::addPoint(std::shared_ptr<PointLight> pointLight) { m_pointLights.push_back(std::move(pointLight)); }

void LightPool::addDir(std::shared_ptr<DirLight> dirLight) { m_dirLights.push_back(std::move(dirLight)); }

void LightPool::addSpot(std::shared_ptr<SpotLight> spotLight) { m_spotLights.push_back(std::move(spotLight)); }

}  // namespace daft::engine