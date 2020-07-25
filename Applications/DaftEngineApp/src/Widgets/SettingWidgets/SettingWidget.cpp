//
// Created by mathis on 12/07/2020.
//
#include "SettingWidget.hpp"

namespace daft::app {
SettingWidget::SettingWidget(DrawableSettings *settings, TransformSettings *transforms, QWidget *parent)
    : QScrollArea(parent), m_settings{settings}, m_transforms{transforms} {
    auto layout = new QVBoxLayout;
    layout->setMargin(2);
    layout->addWidget(settings);
    layout->addWidget(transforms);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setWidget(widget);
    setMinimumWidth(widget->width() + 16);
    setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
}

}  // namespace daft::app