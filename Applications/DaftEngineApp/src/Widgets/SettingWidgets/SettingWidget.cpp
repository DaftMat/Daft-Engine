//
// Created by mathis on 12/07/2020.
//
#include "SettingWidget.hpp"

namespace daft::app {
SettingWidget::SettingWidget(DrawableSettings *settings, QWidget *parent) : QWidget(parent), m_settings{settings} {}
}  // namespace daft::app