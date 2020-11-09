//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Rendering/FrameBufferObject.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Light/LightPool.hpp>
#include <Engine/Renderer/Cameras/Camera.hpp>
#include <Engine/Renderer/RenderPasses/HDRPass.hpp>
#include <memory>
#include <vector>

namespace daft {
/// forwards
namespace core {
class FrameBufferObject;
class ShaderProgram;
}  // namespace core
namespace engine {
class QuadRenderer;
class MultiSamplingPass;

class ENGINE_API Renderer : public daft::core::NonCopyable {
   public:
    enum class AvailableShaders { BlinnPhong, Phong, None };

    /**
     * Default constructor.
     */
    Renderer() = default;

    /**
     * Standard constructor.
     * @param width - width of the viewport.
     * @param height - height of the viewport.
     */
    Renderer(int width, int height);

    /**
     * Destructor.
     */
    ~Renderer() noexcept = default;

    /**
     * Move constructor.
     * @param other - renderer to move.
     */
    Renderer(Renderer &&other) noexcept = default;

    /**
     * Move assignment operator.
     * @param other - renderer to move.
     * @return ref to this.
     */
    Renderer &operator=(Renderer &&other) noexcept = default;

    /**
     * Prepare to render the next frame.
     */
    void prepare();

    /**
     * Render the next frame.
     */
    void render();

    /**
     * Resizes the viewport.
     * @param width - new width.
     * @param height - new height.
     */
    void resize(int width, int height);

    /**
     * Getter for the current selected drawable in the scene.
     * @return the current selection.
     */
    Drawable *getSelection();

    /**
     * Getter for the root of the scene tree.
     * @return the root of the scene tree.
     */
    Composite *getSceneTree() { return m_root.get(); }

    /**
     * Sets the current selection through its name.
     * @param s - name of the drawable wanted.
     */
    void setSelection(std::string s);

    /**
     * Adds a drawable to the scene tree.
     * @param drawable - drawable to add.
     */
    void addDrawable(Drawable::Type type) { m_addNextFrame.push_back(type); }

    void addCustomObject(std::string filePath);

    /**
     * Removes the current selected drawable from the scene tree.
     */
    void removeSelection() { m_removeNextFrame = true; }

    /**
     * Process the event when the mouse's scroll is moved.
     * @param offset - how much the scroll move.
     */
    void processMouseScroll(float offset);

    /**
     * Process the event when one mouse's button is pressed
     * @param mouse - information of the mouse, see Mouse .
     */
    void processMousePress(Camera::Mouse mouse);

    /**
     * Process the event when one mouse's button is released.
     */
    void processMouseRelease();

    /**
     * Process the event when the mouse is being moved.
     * @param mousePos - current position of the mouse.
     */
    void processMouseMove(glm::vec2 mousePos);

    /**
     * Updates the view matrix in all the shaders
     */
    void updateViewMatrix();

    /**
     * Updates the projection matrix in all the shaders.
     */
    void updateProjectionMatrix();

    /**
     * Change the lighting shader being used on the scene.
     * @param shader - new shader to use.
     */
    void setShader(AvailableShaders shader) { m_newShader = shader; }

    void setExposure(float exposure) { m_HDRPass->exposure() = exposure; }

    float exposure() const { return m_HDRPass->exposure(); }

    /**
     * Changes sky color to default grey and starts render edges.
     */
    void switchToEditionMode();

    /**
     * Changes sky color to blue sky and stops render edges.
     */
    void switchToRenderingMode();

   private:
    void clearGL() const;
    void _removeSelection();
    void _addDrawable();
    void _setSelection();
    void _setShader();
    void buildGrid(int size = 50);
    void drawGrid() const;

    static bool GLinitialized;
    int m_width{0}, m_height{0};
    std::string m_selection;

    std::shared_ptr<Composite> m_root{nullptr};
    std::unique_ptr<LightPool> m_lightPool{nullptr};

    std::shared_ptr<QuadRenderer> m_screenQuad{nullptr};
    std::shared_ptr<MultiSamplingPass> m_multisamplePass{nullptr};
    std::shared_ptr<HDRPass> m_HDRPass{nullptr};

    std::vector<std::shared_ptr<core::ShaderProgram>> m_shaders;
    std::vector<core::FrameBufferObject> m_fbos;

    daft::engine::Camera m_camera;

    bool m_removeNextFrame{false};
    std::vector<Drawable::Type> m_addNextFrame;
    std::string m_filePathCustom;
    AvailableShaders m_newShader{AvailableShaders::None};

    glm::vec3 m_defaultSkyColor{0.35, 0.35, 0.35};
    bool m_drawEdges{true};

    std::unique_ptr<core::ShaderProgram> m_shadowShader{nullptr};

    struct Grid {
        core::Mesh grid;
        std::vector<core::Mesh> axis;
    } m_grid;
};
}  // namespace engine
}  // namespace daft