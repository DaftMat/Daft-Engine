//
// Created by mathis on 10/07/2020.
//
#include "BorderWidget.hpp"

#include <QtWidgets/QHBoxLayout>

namespace daft::app {
BorderWidget::BorderWidget(Orientation orientation, int minSize, QWidget *parent)
    : QWidget(parent), m_orientation{orientation} {
    switch (m_orientation) {
        case Orientation::HORIZONTAL:
            m_layout = std::make_unique<QHBoxLayout>();
            setMinimumHeight(minSize);
            break;
        case Orientation::VERTICAL:
            m_layout = std::make_unique<QVBoxLayout>();
            setMinimumWidth(minSize);
            break;
    }
    setLayout(m_layout.get());
}

void BorderWidget::addSeparator() {
    switch (m_orientation) {
        case Orientation::HORIZONTAL:
            m_layout->addWidget(createLine(QFrame::VLine));
            break;
        case Orientation::VERTICAL:
            m_layout->addWidget(createLine(QFrame::HLine));
            break;
    }
}

void BorderWidget::addSpacer() {
    switch (m_orientation) {
        case Orientation::HORIZONTAL:
            m_layout->addItem(createHSpacer());
            break;
        case Orientation::VERTICAL:
            m_layout->addItem(createVSpacer());
            break;
    }
}

QFrame *BorderWidget::createLine(QFrame::Shape shape) {
    auto frame = new QFrame();
    frame->setFrameShape(shape);
    frame->setFrameShadow(QFrame::Plain);
    return frame;
}

QSpacerItem *BorderWidget::createHSpacer(int size) {
    return new QSpacerItem(size * 2, size, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem *BorderWidget::createVSpacer(int size) {
    return new QSpacerItem(size, size * 2, QSizePolicy::Minimum, QSizePolicy::Expanding);
}
}  // namespace daft::app