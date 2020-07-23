//
// Created by mathis on 10/07/2020.
//
#include "BorderWidget.hpp"

#include <QtWidgets/QHBoxLayout>

#include "MainWidget.hpp"

namespace daft::app {
BorderWidget::BorderWidget(Orientation orientation, int minSize, int maxSize, QWidget *parent)
    : QWidget(parent), m_orientation{orientation} {
    switch (m_orientation) {
        case Orientation::HORIZONTAL:
            m_layout = std::make_unique<QHBoxLayout>();
            setMinimumHeight(minSize);
            setMaximumHeight(maxSize);
            break;
        case Orientation::VERTICAL:
            m_layout = std::make_unique<QVBoxLayout>();
            setMinimumWidth(minSize);
            setMaximumWidth(maxSize);
            break;
    }
    setLayout(m_layout.get());
}

void BorderWidget::addSeparator() {
    switch (m_orientation) {
        case Orientation::HORIZONTAL:
            m_layout->addWidget(MainWidget::createLine(QFrame::VLine));
            break;
        case Orientation::VERTICAL:
            m_layout->addWidget(MainWidget::createLine(QFrame::HLine));
            break;
    }
}

void BorderWidget::addSpacer() {
    switch (m_orientation) {
        case Orientation::HORIZONTAL:
            m_layout->addItem(MainWidget::createHSpacer());
            break;
        case Orientation::VERTICAL:
            m_layout->addItem(MainWidget::createVSpacer());
            break;
    }
}
}  // namespace daft::app