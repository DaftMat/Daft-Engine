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
     * @param enablePos - is position transformation enabled
     * @param enableRot - is rotation transformation enabled
     * @param enableSca - is scale transformation enabled
     * @param parent - parent of the widget.
     */
    explicit TransformSettings(daft::core::SettingManager settings, bool enablePos = true, bool enableRot = true,
                               bool enableSca = true, QWidget *parent = nullptr);

    /**
     * Transformation settings constant reference getter.
     * @return const ref to the transformation settings of the drawable.
     */
    [[nodiscard]] const core::SettingManager &transforms() const { return m_settings; }

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

    daft::core::SettingManager m_settings;
};
}  // namespace daft::app