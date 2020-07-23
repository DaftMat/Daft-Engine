//
// Created by mathis on 23/07/2020.
//
#pragma once

#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QWidget>
#include <memory>

namespace daft::app {
class DrawableSettings : public QWidget {
   public:
    explicit DrawableSettings(daft::core::mat::SettingManager *settings, QWidget *parent = nullptr)
        : QWidget(parent), m_settings{settings}, m_layout{new QFormLayout()} {
        setLayout(m_layout.get());
    }

    ~DrawableSettings() override { m_layout.reset(); }

   public slots:
    virtual void onDrawableChanged() = 0;

   private:
    std::unordered_map<std::string, std::vector<QWidget *>> m_fields;
    std::shared_ptr<daft::core::mat::SettingManager> m_settings{nullptr};

    std::unique_ptr<QFormLayout> m_layout;

   protected:
    void addField(std::string label, std::vector<QWidget *> widgets);
};
}  // namespace daft::app