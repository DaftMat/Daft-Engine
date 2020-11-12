//
// Created by mathis on 23/05/2020.
//
#include "Renderer.hpp"

#include <Core/Random.hpp>
#include <Core/Rendering/ShaderProgram.hpp>
#include <Core/Utils/Logger.hpp>
#include <Engine/Drawables/Object/BSpline2D.hpp>
#include <Engine/Drawables/Object/primitiveIncludes.hpp>
#include <Engine/Renderer/QuadRenderer.hpp>
#include <Engine/Renderer/RenderPasses/MultiSamplingPass.hpp>
#include <iostream>

namespace daft::engine {
Renderer::Renderer(int width, int height) {
    m_width = width;
    m_height = height;
    if (!GLinitialized) {
        if (!gladLoadGL()) {
            std::stringstream ss;
            ss << "Failed to load OpenGL.";
            daft::core::Logger::error(std::move(ss));
            exit(-1);
        }
        GLinitialized = true;
    }

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_MULTISAMPLE);
    glDepthFunc(GL_LESS);
    glPointSize(8);

    m_root = std::make_shared<Composite>();
    m_lightPool = std::make_unique<LightPool>();

    m_shaders.push_back(
        std::make_shared<core::ShaderProgram>("shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl"));
    m_shaders[0]->use();
    m_shaders[0]->setBool("instantToneMapping", m_drawEdges);
    m_shaders[0]->stop();
    m_shaders.push_back(std::make_shared<core::ShaderProgram>("shaders/color.vert.glsl", "shaders/color.frag.glsl"));
    m_multisamplePass = std::make_shared<daft::engine::MultiSamplingPass>(m_width, m_height, 32, true);
    m_screenQuad = std::make_shared<daft::engine::QuadRenderer>();
    m_screenQuad->addQuad(-1.f, 1.f, 2.f, 2.f);

    m_HDRPass = std::make_shared<HDRPass>(m_width, m_height, 32);

    m_shadowShader =
        std::make_unique<core::ShaderProgram>("shaders/shadowmap.vert.glsl", "shaders/shadowmap.frag.glsl");

    buildGrid(100);

    updateProjectionMatrix();
    updateViewMatrix();
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    clearGL();

    m_root->update();

    _removeSelection();
    _addDrawable();
    _setSelection();
    _setShader();
}

void Renderer::clearGL() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(m_defaultSkyColor.x, m_defaultSkyColor.y, m_defaultSkyColor.z, 1.f);
}

void Renderer::render() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    /// render shadow maps
    m_shadowShader->use();
    m_lightPool->renderToLightMap(m_root.get(), *m_shadowShader, m_width, m_height, m_camera);
    m_shadowShader->stop();

    if (m_drawEdges) {
        m_screenQuad->quad(0).setTexture(m_multisamplePass->outTexture());
        m_multisamplePass->use();
    } else {
        m_screenQuad->quad(0).setTexture(m_HDRPass->outTexture());
        m_HDRPass->use();
    }
    clearGL();
    /// draw objects
    m_shaders[0]->use();
    /// add lights to shader
    m_lightPool->loadToShader(*m_shaders[0]);
    m_root->render(*m_shaders[0]);
    m_shaders[0]->stop();

    if (m_drawEdges) {
        m_shaders[1]->use();
        /// draw objects' edges
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_shaders[1]->setVec3("color", glm::vec3{0.f});
        m_root->renderEdges(*m_shaders[1]);
        /// draw grid
        m_shaders[1]->setMat4("model", glm::mat4{1.f});
        /// grid
        drawGrid();
        m_shaders[1]->stop();
    }

    /// unbind opengl objects
    if (m_drawEdges) {
        m_multisamplePass->stop(m_width, m_height);
    } else {
        m_HDRPass->stop(m_width, m_height);
    }

    /// render the frame-textured quad to the screen.
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    m_screenQuad->prepare();
    m_screenQuad->render();
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
    updateProjectionMatrix();
}

bool Renderer::GLinitialized{false};

void Renderer::processMouseScroll(float offset) {
    m_camera.processMouseScroll(offset);
    updateViewMatrix();
}

void Renderer::processMousePress(daft::engine::Camera::Mouse mouse) { m_camera.processMousePress(mouse); }

void Renderer::processMouseRelease() { m_camera.processMouseRelease(); }

void Renderer::processMouseMove(glm::vec2 mousePos) {
    m_camera.processMouseMove(mousePos);
    updateViewMatrix();
}

daft::engine::Drawable *Renderer::getSelection() {
    if (m_selection.empty()) return nullptr;
    return m_root->find(m_selection);
}

void Renderer::setSelection(std::string s) {
    auto selection = getSelection();
    if (selection) selection->unselect();
    m_selection = std::move(s);
}

void Renderer::addDrawable(Drawable::Type type, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
    ObjectSpec os{};
    os.type = type;
    os.pos = pos;
    os.rot = rot;
    os.scale = scale;
    m_addNextFrame.push_back(os);
}

void Renderer::addCustomObject(std::string filePath, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
    ObjectSpec os{};
    os.type = Drawable::Type::Custom;
    os.pos = pos;
    os.rot = rot;
    os.scale = scale;
    m_addNextFrame.push_back(os);
    m_filePathCustom = std::move(filePath);
}

void Renderer::updateViewMatrix() {
    for (const auto &shader : m_shaders) {
        shader->use();
        shader->setMat4("view", m_camera.getViewMatrix());
        shader->setVec3("viewPos", m_camera.position());
        shader->stop();
    }
}

void Renderer::updateProjectionMatrix() {
    for (const auto &shader : m_shaders) {
        shader->use();
        shader->setMat4("projection", glm::perspective(m_camera.fov(), float(m_width) / float(m_height), 0.1f, 500.f));
        shader->stop();
    }
}

void Renderer::switchToEditionMode() {
    m_drawEdges = true;
    m_shaders[0]->use();
    m_shaders[0]->setBool("instantToneMapping", m_drawEdges);
    m_shaders[0]->stop();
    m_defaultSkyColor = {0.35, 0.35f, 0.35f};
}

void Renderer::switchToRenderingMode() {
    m_drawEdges = false;
    m_shaders[0]->use();
    m_shaders[0]->setBool("instantToneMapping", m_drawEdges);
    m_shaders[0]->stop();
    m_defaultSkyColor = {0.52f, 0.81f, 0.92f};
}

void Renderer::_removeSelection() {
    if (m_removeNextFrame) {
        auto selection = getSelection();
        if (selection && selection->isLight()) {
            m_lightPool->remove(m_selection);
        }
        m_root->remove(m_selection);
        m_removeNextFrame = false;
    }
}

void Renderer::_addDrawable() {
    for (auto objSpec : m_addNextFrame) {
        std::shared_ptr<Drawable> drawable{nullptr};
        switch (objSpec.type) {
            case Drawable::Type::Group:
                drawable = std::make_shared<Composite>();
                break;
            case Drawable::Type::Sphere:
                drawable = std::make_shared<Sphere>();
                break;
            case Drawable::Type::Torus:
                drawable = std::make_shared<Torus>();
                break;
            case Drawable::Type::Cube:
                drawable = std::make_shared<Cube>();
                break;
            case Drawable::Type::Cylinder:
                drawable = std::make_shared<Cylinder>();
                break;
            case Drawable::Type::Metaballs:
                drawable = std::make_shared<Metaballs>();
                break;
            case Drawable::Type::Caves:
                drawable = std::make_shared<Caves>();
                break;
            case Drawable::Type::BSpline: {
                std::vector<glm::vec3> controlPoints;
                controlPoints.emplace_back(glm::vec3{0.f});
                drawable = std::make_shared<BSpline>(controlPoints, 1);
                break;
            }
            case Drawable::Type::BSpline2D: {
                std::vector<std::vector<glm::vec3>> controlPoints;
                int n = 10;
                for (int i = -n; i <= n; ++i) {
                    std::vector<glm::vec3> subControlPoints;
                    for (int j = -n; j <= n; ++j) {
                        subControlPoints.emplace_back(float(i), core::Random::get(-2.f, 2.f), float(j));
                    }
                    controlPoints.push_back(subControlPoints);
                    subControlPoints.clear();
                }
                for (auto &poly : controlPoints)
                    for (auto &point : poly) point.y = core::Random::get(-1.f, 1.f);
                drawable = std::make_shared<BSpline2D>(controlPoints, 2, n * 10);
                break;
            }
            case Drawable::Type::Custom: {
                drawable = std::make_shared<Object>(std::move(m_filePathCustom));
                m_filePathCustom.clear();
                break;
            }
            case Drawable::Type::PointLight: {
                auto toAdd = std::make_shared<PointLight>();
                drawable = toAdd;
                m_lightPool->addPoint(toAdd);
                break;
            }
            case Drawable::Type::DirLight: {
                auto toAdd = std::make_shared<DirLight>();
                drawable = toAdd;
                m_lightPool->addDir(toAdd);
                break;
            }
            case Drawable::Type::SpotLight: {
                auto toAdd = std::make_shared<SpotLight>();
                drawable = toAdd;
                m_lightPool->addSpot(toAdd);
                break;
            }
            default:
                break;
        }

        if (drawable) {
            drawable->position() = objSpec.pos;
            drawable->rotations() = objSpec.rot;
            drawable->scale() = objSpec.scale;
            auto selection = getSelection();
            if (selection && selection->isComposite()) {
                dynamic_cast<daft::engine::Composite *>(selection)->add(drawable);
            } else {
                m_root->add(drawable);
            }
        }
    }
    m_addNextFrame.clear();
}

void Renderer::_setSelection() {
    auto selection = getSelection();
    if (selection && !selection->selected()) {
        selection->select();
    }
}

void Renderer::_setShader() {
    switch (m_newShader) {
        case Renderer::AvailableShaders::BlinnPhong:
            m_shaders[0].reset();
            m_shaders[0] =
                std::make_shared<core::ShaderProgram>("shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl");
            break;
        case Renderer::AvailableShaders::Phong:
            m_shaders[0].reset();
            m_shaders[0] = std::make_shared<core::ShaderProgram>("shaders/phong.vert.glsl", "shaders/phong.frag.glsl");
        default:
            break;
    }
    m_newShader = Renderer::AvailableShaders::None;
    updateViewMatrix();
    updateProjectionMatrix();
}

void Renderer::buildGrid(int size) {
    std::vector<glm::vec3> positions;
    std::vector<GLuint> indices;

    /// grid
    GLuint index;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            index = GLuint(i + j * size);
            positions.emplace_back(float(i) - float(size) / 2.f, 0.f, float(j) - float(size) / 2.f);

            if (i < size && j < size && (i != size / 2 || j != size / 2)) {
                if (i < size - 1) {
                    indices.push_back(index);
                    indices.push_back(index + 1);
                }
                if (j < size - 1) {
                    indices.push_back(index);
                    indices.push_back(index + size);
                }
            }
        }
    }

    core::AttribManager amGrid;
    amGrid.addAttrib(positions);
    amGrid.indices() = indices;
    m_grid.grid.reset(std::move(amGrid));

    /// arrows
    positions.clear();
    indices.clear();
    indices.push_back(0);
    indices.push_back(1);
    positions.emplace_back(0.f, 0.f, 0.f);
    positions.emplace_back(0.f, 0.f, 0.f);
    for (int i = 0; i < 3; ++i) {
        positions[1] = core::axis()[i];
        core::AttribManager amAxis;
        amAxis.addAttrib(positions);
        amAxis.indices() = indices;
        m_grid.axis.emplace_back(std::move(amAxis));
    }
}

void Renderer::drawGrid() const {
    /// grid
    m_shaders[1]->setVec3("color", glm::vec3{0.1f});
    m_grid.grid.prepare();
    m_grid.grid.render(GL_LINES);
    m_grid.grid.unbind();
    /// axis
    for (int i = 0; i < 3; ++i) {
        m_shaders[1]->setVec3("color", core::axis()[i]);
        m_grid.axis[i].prepare();
        m_grid.axis[i].render(GL_LINES);
        m_grid.axis[i].unbind();
    }
}

}  // namespace daft::engine