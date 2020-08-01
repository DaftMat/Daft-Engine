//
// Created by mathis on 12/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/OpenGL.hpp>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QWidget>
#include <array>

namespace daft::app {
/**
 * A class to edit the transformations of the selected object.
 */
class ENGINE_API TransformSettings : public QWidget {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - library of the selected object's settings.
     * @param parent - parent of the widget.
     */
    explicit TransformSettings(daft::core::mat::SettingManager settings, QWidget *parent = nullptr);

   public slots:
    void onTransformChanged();

   signals:
    void settingChanged();

   private:
    enum class Type { POSITION, ROTATION, SCALE };

    using QDoubleSpinBoxPtr = QDoubleSpinBox *;

    QWidget *createTransformWidget(Type type);

    std::array<QDoubleSpinBoxPtr, 3> m_position{nullptr, nullptr, nullptr};
    std::array<QDoubleSpinBoxPtr, 3> m_rotations{nullptr, nullptr, nullptr};
    std::array<QDoubleSpinBoxPtr, 3> m_scale{nullptr, nullptr, nullptr};

    daft::core::mat::SettingManager m_settings;
};
}  // namespace daft::app