//
// Created by daftmat on 23/09/2020.
//

#pragma once
#include <API.hpp>
#include "Object.hpp"

namespace daft::engine {
    class ENGINE_API BSpline : public Object {
    public:
        explicit BSpline(std::vector<glm::vec3> controlPoints, Composite *parent = nullptr, std::string name = "BSpline"+std::to_string(m_nrBSpline)) : Object(parent, std::move(name)), m_controlPoints{std::move(controlPoints)} {
            createBSpline();
        }

        ~BSpline() override = default;

        BSpline(BSpline &&) noexcept = default;

        BSpline &operator=(BSpline &&) noexcept = default;

        void render(const core::ShaderProgram &shader) override {}

        void renderEdges(const core::ShaderProgram &shader) override;

        [[nodiscard]] core::SettingManager getSettings() const override { return core::SettingManager{}; }

        void setSettings(const core::SettingManager &s) override {}

    private:
        void createBSpline();

        std::vector<glm::vec3> m_controlPoints;

        static int m_nrBSpline;
    };
}
