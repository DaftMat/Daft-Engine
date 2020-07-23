//
// Created by mathis on 23/07/2020.
//
#include "DrawableSettings.hpp"

namespace daft::app {
void DrawableSettings::addField(std::string label, std::vector<QWidget *> widgets) {
    auto *fieldLayout = new QHBoxLayout();
    for (auto widget : widgets) {
        fieldLayout->addWidget(widget);
    }
    m_layout->addRow(label.c_str(), fieldLayout);
    m_fields.insert(std::make_pair(std::move(label), std::move(widgets)));
}
}  // namespace daft::app
