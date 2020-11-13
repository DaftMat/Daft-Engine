//
// Created by mathis on 12/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/OpenGL.hpp>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <array>
#include <memory>

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

    /**
     * Mouse press action
     * @param event - mouse infos
     */
    void mousePressEvent(QMouseEvent *event) override;

   public slots:
    void onTransformChanged();
    void on_titleClicked();

   signals:
    void settingChanged();
    void titleClicked();
    void updateEvent();

   private:
    enum class Type { POSITION, ROTATION, SCALE };

    using QDoubleSpinBoxPtr = QDoubleSpinBox *;

    QWidget *createTransformWidget(Type type);

    std::array<QDoubleSpinBoxPtr, 3> m_position{nullptr, nullptr, nullptr};
    std::array<QDoubleSpinBoxPtr, 3> m_rotations{nullptr, nullptr, nullptr};
    std::array<QDoubleSpinBoxPtr, 3> m_scale{nullptr, nullptr, nullptr};

    daft::core::SettingManager m_settings;

    std::unique_ptr<QLabel> m_title;
    std::unique_ptr<QWidget> m_widget;
};
}  // namespace daft::app