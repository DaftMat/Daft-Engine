//
// Created by daftmat on 28/09/2020.
//

#include "SphereSettings.hpp"

namespace daft::app {
SphereSettings::SphereSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    engine::Sphere::Type type{m_settings.get<int>("Type")};

    addComboBox("Type", {"UV", "Icosahedron", "Cube", "Fibonacci"}, core::toUType(type));
    switch (type) {
        case engine::Sphere::Type::UV:
            addIntSpinBox("Meridians", 3, 9999, 1);
            addIntSpinBox("Parallels", 3, 9999, 1);
            break;
        case engine::Sphere::Type::Ico:
            addIntSpinBox("Subdivisions", 0, 999, 1);
            break;
        case engine::Sphere::Type::Cube:
            addIntSpinBox("Resolution", 2, 9999, 1);
            break;
        case engine::Sphere::Type::Fibo:
            addIntSpinBox("Points", 8, 999999, 10);
            break;
    }
    addDoubleSpinBox("Radius", 0, 9999, 0.1);
}
}  // namespace daft::app