//
// Created by mathis on 12/07/2020.
//
#include "SettingWidget.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QLabel>

namespace daft::app {
SettingWidget::SettingWidget(DrawableSettings *settings, TransformSettings *transforms, std::string name,
                             QWidget *parent)
    : QScrollArea(parent), m_settings{settings}, m_transforms{transforms} {
    auto layout = new QVBoxLayout;
    layout->setMargin(2);

    std::string pname;
    if (m_settings == nullptr && m_transforms == nullptr)
        pname = "No object selected.";
    else
        pname = std::move(name);
    auto title = new QLabel(pname.c_str());
    title->setObjectName("sectionTitle");
    layout->addWidget(title);
    if (m_settings != nullptr) layout->addWidget(settings);
    if (m_transforms != nullptr) layout->addWidget(transforms);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setWidget(widget);
    auto screenWidth = float(QApplication::desktop()->screenGeometry().width());
    setMinimumWidth(int(screenWidth / 5.5f));
    setObjectName("settingWidget");
    setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    if (m_settings != nullptr) connect(m_settings.get(), SIGNAL(settingChanged()), this, SLOT(on_settingChanged()));
    if (m_transforms != nullptr) connect(m_transforms.get(), SIGNAL(settingChanged()), this, SLOT(on_settingChanged()));
}

}  // namespace daft::app