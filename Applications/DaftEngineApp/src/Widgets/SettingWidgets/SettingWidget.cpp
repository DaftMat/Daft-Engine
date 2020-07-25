//
// Created by mathis on 12/07/2020.
//
#include "SettingWidget.hpp"

#include <QtWidgets/QLabel>

namespace daft::app {
SettingWidget::SettingWidget(DrawableSettings *settings, TransformSettings *transforms, std::string name,
                             QWidget *parent)
    : QScrollArea(parent), m_settings{settings}, m_transforms{transforms} {
    auto layout = new QVBoxLayout;
    layout->setMargin(2);

    std::string pname = std::move(name);
    std::string resname = pname + (*(pname.end()) == 's' ? "' " : "'s ") + "panel";
    layout->addWidget(new QLabel(resname.c_str()));
    layout->addWidget(settings);
    layout->addWidget(transforms);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setWidget(widget);
    setMinimumWidth(widget->width() + 16);
    setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
}

}  // namespace daft::app