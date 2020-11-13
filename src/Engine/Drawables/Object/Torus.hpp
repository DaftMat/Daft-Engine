//
// Created by mathis on 10/09/2020.
//
#pragma once
#include <API.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API Torus : public Object {
   public:
    /**
     * Standard constructor.
     * @param meridians - meridians of the torus.
     * @param parallels - parallels of the torus.
     * @param innerRadius - inner radius of the torus.
     * @param outerRadius - outer radius of the torus.
     * @param parent - parent Composite .
     * @param name - name of the torus.
     */
    explicit Torus(int meridians = 32, int parallels = 16, float innerRadius = 1.f, float outerRadius = 0.5f,
                   Composite *parent = nullptr, std::string name = "Torus" + std::to_string(m_nrTorus++));

    /**
     * Default destructor.
     */
    ~Torus() override = default;

    /**
     * Default move constructor.
     */
    Torus(Torus &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Torus &operator=(Torus &&) noexcept = default;

    /**
     * Gets the sphere's specific settings as a SettingManager .
     * @return settings.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Settings setter using a SettingManager .
     * @param s - settings.
     */
    void setSettings(const core::SettingManager &s) override;

    /**
     * Meridians getter.
     * @return meridians.
     */
    [[nodiscard]] int meridians() const { return m_meridians; }

    /**
     * Meridians setter.
     * @param m - new value for meridians.
     */
    void setMeridians(int m);

    /**
     * Parallels getter.
     * @return parallels.
     */
    [[nodiscard]] int parallels() const { return m_parallels; }

    /**
     * Parallels setter.
     * @param p - new value for parallels.
     */
    void setParallels(int p);

    /**
     * Inner radius getter.
     * @return inner radius.
     */
    [[nodiscard]] float innerRadius() const { return m_innerRadius; }

    /**
     * Inner radius setter.
     * @param r - new value for the inner radius.
     */
    void setInnerRadius(float r);

    /**
     * Outer radius getter.
     * @return outer radius.
     */
    [[nodiscard]] float outerRadius() const { return m_outerRadius; }

    /**
     * Outer radius setter.
     * @param r - new value for outer radius.
     */
    void setOuterRadius(float r);

    /**
     * Accepts a visitor.
     * @param visitor - visitor to be accepted.
     */
    void accept(core::DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return Type::Torus .
     */
    [[nodiscard]] Type getType() const override { return Type::Torus; }

   protected:
    void applyUpdate() override { createTorus(); }

   private:
    void createTorus();

    int m_meridians{32};
    int m_parallels{16};
    float m_innerRadius{1.f};
    float m_outerRadius{0.5f};

    static int m_nrTorus;
};
}  // namespace daft::engine