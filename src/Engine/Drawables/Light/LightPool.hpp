//
// Created by mathis on 11/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <memory>
#include <string>
#include <vector>

namespace daft {
namespace core {
class ShaderProgram;
}
namespace engine {
class PointLight;
class DirLight;
class SpotLight;

class ENGINE_API LightPool : public core::NonCopyable {
   public:
    /**
     * Default constructor.
     */
    LightPool() = default;

    /**
     * Default destructor.
     */
    ~LightPool() = default;

    /**
     * Default move constructor.
     */
    LightPool(LightPool &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    LightPool &operator=(LightPool &&) noexcept = default;

    /**
     * Loads all the lights in a shader as uniform structs.
     * @param shader - shader to add the lights to.
     */
    void loadToShader(const core::ShaderProgram &shader) const;

    /**
     * Adds a PointLight to the pool.
     * @param pointLight - point light to add.
     */
    void add(std::shared_ptr<PointLight> pointLight);

    /**
     * Adds a DirLight to the pool.
     * @param dirLight - dir light to add.
     */
    void add(std::shared_ptr<DirLight> dirLight);

    /**
     * Adds a SpotLight to the pool.
     * @param spotLight - spot light to add.
     */
    void add(std::shared_ptr<SpotLight> spotLight);

    /**
     * Removes a light from the pool.
     * @param name - name of the light to remove.
     */
    void remove(const std::string &name);

   private:
    std::vector<std::shared_ptr<PointLight>> m_pointLights;
    std::vector<std::shared_ptr<DirLight>> m_dirLights;
    std::vector<std::shared_ptr<SpotLight>> m_spotLights;
};
}  // namespace engine
}  // namespace daft