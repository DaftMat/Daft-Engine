//
// Created by mathis on 12/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/OpenGL.hpp>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QWidget>

namespace daft::app {
class ENGINE_API TransformSettings : public QWidget {
    Q_OBJECT
   public:
    explicit TransformSettings(daft::core::mat::SettingManager *settings, QWidget *parent = nullptr);

    ~TransformSettings() override;

   public slots:
    void onTransformChanged(double val);

   private:
    enum class Type { POSITION, ROTATION, SCALE };

    using QDoubleSpinBoxPtr = QDoubleSpinBox *;

    QWidget *createTransformWidget(Type type);

    std::array<QDoubleSpinBoxPtr, 3> m_position{nullptr, nullptr, nullptr};
    std::array<QDoubleSpinBoxPtr, 3> m_rotations{nullptr, nullptr, nullptr};
    std::array<QDoubleSpinBoxPtr, 3> m_scale{nullptr, nullptr, nullptr};

    std::shared_ptr<daft::core::mat::SettingManager> m_settings{nullptr};
};
}  // namespace daft::app