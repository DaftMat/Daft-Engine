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
    LightPool() = default;

    ~LightPool() = default;

    LightPool(LightPool &&) noexcept = default;

    LightPool &operator=(LightPool &&) noexcept = default;

    void loadToShader(const core::ShaderProgram &shader) const;

    void add(std::shared_ptr<PointLight> pointLight);

    void add(std::shared_ptr<DirLight> dirLight);

    void add(std::shared_ptr<SpotLight> spotLight);

    void remove(const std::string &name);

   private:
    std::vector<std::shared_ptr<PointLight>> m_pointLights;
    std::vector<std::shared_ptr<DirLight>> m_dirLights;
    std::vector<std::shared_ptr<SpotLight>> m_spotLights;
};
}  // namespace engine
}  // namespace daft