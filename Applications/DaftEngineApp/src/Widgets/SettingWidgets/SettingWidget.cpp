//
// Created by mathis on 12/07/2020.
//
#include "SettingWidget.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QLabel>

namespace daft::app {
SettingWidget::SettingWidget(DrawableSettings *settings, TransformSettings *transforms, std::string name,
                             float exposure, QWidget *parent)
    : QScrollArea(parent), m_settings{settings}, m_transforms{transforms} {
    std::string pname;
    if (m_settings == nullptr && m_transforms == nullptr) {
        pname = "Scene settings";
        core::SettingManager sm;
        sm.add("Exposure", exposure);
        m_settings = std::make_unique<DrawableSettings>(sm);
        m_settings->addDoubleSpinBox("Exposure", 0.01, 999.9, 0.1);
    } else
        pname = std::move(name);
    m_title = new QLabel(pname.c_str());
    m_title->setObjectName("sectionTitle");
    createWidgets();
    if (m_settings != nullptr) connect(m_settings.get(), SIGNAL(updateEvent()), this, SLOT(on_updateEvent()));
    if (m_transforms != nullptr) connect(m_transforms.get(), SIGNAL(updateEvent()), this, SLOT(on_updateEvent()));
}

void SettingWidget::setTitle(const std::string &name) { m_title->setText(name.c_str()); }

void SettingWidget::on_updateEvent() { createWidgets(); }

void SettingWidget::createWidgets() {
    m_layout = std::make_unique<QVBoxLayout>();
    m_layout->setMargin(1);
    m_layout->addWidget(m_title);
    if (m_settings != nullptr) m_layout->addWidget(m_settings.get());
    if (m_transforms != nullptr) m_layout->addWidget(m_transforms.get());

    auto widget = new QWidget;
    widget->setLayout(m_layout.get());

    setWidget(widget);
    auto screenWidth = float(QApplication::desktop()->screenGeometry().width());
    setMinimumWidth(int(screenWidth / 5.5f));
    setObjectName("settingWidget");
    setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
}

}  // namespace daft::app